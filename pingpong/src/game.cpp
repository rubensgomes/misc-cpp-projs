// Copyright (C) 2016 Rubens S. Gomes <rubens.s.gomes@gmail.com>

#include "game.hpp"

#include <boost/iterator/iterator_facade.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/special_functions/binomial.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include <cstdbool>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stdexcept>


Game* Game::sInstance = NULL;

Game* Game::instance(const std::string dataFile)
{
    if(sInstance == NULL)
    {
        sInstance = new Game(dataFile);
    }

    return sInstance;
}

// overload << operator
std::ostream& operator<<(std::ostream & strm, const Game & rhs)
{
    std::string str;
    if(rhs.getBracket().empty())
    {
        str = "Tournament does not have players";
    }
    else
    {
        std::stringstream sstream;
        for(const auto match : rhs.getBracket())
        {
            sstream << *match << std::endl;
        }
        str = sstream.str();
    }

    return strm << str;
}

Game::Game(){}

Game::~Game()
{
    if(! mPlayers.empty())
    {
        for(const auto& player : mPlayers)
        {
            delete player;
        }
    }
}

Game::Game(const std::string dataFile)
{
    loadPlayersFromCSVFile(dataFile);
    loadBracket();
    mNrGames = calculateNrGames(mPlayers.size());
}

void Game::loadPlayersFromCSVFile(const std::string & dataFile)
{
    // open and check file.
    std::ifstream infile;
    infile.open(dataFile, std::ios::in);
    if(! infile.is_open())
    {
        throw std::invalid_argument("File [" + dataFile + 
            "] failed to open.");
    }

    // read and process every line in file
    std::string items[CSV_COLUMNS];
    int i = 0 ; std::string line; bool skipLine = true;
    typedef boost::tokenizer<boost::escaped_list_separator<char> > tokenizer;

    int lineNr = 0;
    while ( std::getline(infile, line) && (lineNr < NR_PLAYERS) )
    {

        // skip CSV headings
        if(skipLine)
        {
            skipLine = false;
            continue;
        }

        i = 0;
        tokenizer tokens(line);

        for (tokenizer::iterator tokIter = tokens.begin();
             tokIter != tokens.end(); ++tokIter)
        {

            if(i >= CSV_COLUMNS)
            {
                throw new std::invalid_argument("File [" +
                        dataFile + "] is not valid");
            }

            items[i++] = *tokIter;
        }

        mPlayers[lineNr++] = new Player (items[0],
                                items[6],
                                atoi(items[4].c_str()),
                                atoi(items[3].c_str()),
                                atoi(items[5].c_str()),
                                atoi(items[1].c_str()),
                                atoi(items[2].c_str()));
    }

    // close data file
    infile.close();

}

void Game::loadBracket()
{
    if( (mPlayers.empty()) || (mPlayers.size() != NR_PLAYERS) )
    {
        throw std::runtime_error("Invalid nr of players.");
    }

    // simplicity for now: manually set up bracket by hand
    mBracket[0] = new Match(*mPlayers[0], *mPlayers[1]);
    mBracket[1] = new Match(*mPlayers[0], *mPlayers[2]);
    mBracket[2] = new Match(*mPlayers[1], *mPlayers[2]);
}

void Game::run()
{
    if(mPlayers.empty())
    {
        throw new std::runtime_error("No players found.");
    }

    if(mBracket.empty())
    {
        throw new std::runtime_error("No tournament bracket found.");
    }

    for(auto match: mBracket)
    {
        // following call is recursive !!!
        playPoint(*match,
                  &match->getPlayerB(),
                  &match->getPlayerA(),
                  true,
                  0,
                  &match->getPlayerA());
    }
}

// recursive method
void Game::playPoint(Match& match,
                     Player* returningPlayer,
                     Player* otherPlayer,
                     bool serving,
                     int alternatePoints,
                     Player* servingPlayer)
{
    if( match.isMatchOver() ) // recursive base case
    {
        match.setMatchOver(true);

        if(match.getPlayerAScore() == FINAL_SCORE)
        {
            match.setWinner(match.getPlayerA());
        }
        else
        {
            match.setWinner(match.getPlayerB());
        }

        std::cout << match.getWinner()->getName()
                  << " wins the game!"
                  << std::endl
                  << std::endl;
        return;
    }

    if(serving) // player is serving
    {

        // ensure returning player is not serving.
        if(returningPlayer == servingPlayer)
        {
            returningPlayer = otherPlayer;
        }

        std::cout << servingPlayer->getName()
                  << " serves to "
                  << returningPlayer->getName()
                  << "...";

        if(! isInBound(servingPlayer->getServeAccuracy()))
        {
            std::cout << " out of bounds." << std::endl;
            std::cout << servingPlayer->getName()
                      << " fails to serve." << std::endl;

            if(match.getPlayerA() == *servingPlayer)
            {
                match.incPlayerBScore();
            }
            else
            {
                match.incPlayerAScore();
            }

            std::cout << otherPlayer->getName()
                      << " gets a point!" << std::endl;

            std::cout << "The score is "
                      << match.getPlayerA().getName()
                      << " "  << match.getPlayerAScore()
                      << ", " << match.getPlayerB().getName()
                      << " "  << match.getPlayerBScore()
                      << "."  << std::endl
                      << std::endl;

            serving = true;
            ++alternatePoints;

            if(alternatePoints == MAX_ALTERNATING_POINTS)
            {
                alternatePoints = 0;
                Player* serv = servingPlayer;

                if(servingPlayer == otherPlayer)
                {
                    servingPlayer = returningPlayer;
                    returningPlayer = serv;
                }
                else
                {
                    servingPlayer = otherPlayer;
                    returningPlayer = serv;
                    otherPlayer = serv;
                }

            }

        }
        else // in-bounds
        {
            std::cout << " in-bounds." << std::endl;
            serving = false;

            // ensure other player is not serving.
            if(otherPlayer == servingPlayer)
            {
                otherPlayer = returningPlayer;
            }

        }
    }
    else // player is returning
    {

        // ensure other player is not returning.
        if(otherPlayer == returningPlayer)
        {
            otherPlayer = servingPlayer;
        }

        std::cout << returningPlayer->getName()
                  << " returns to "
                  << otherPlayer->getName()
                  << "...";

        if(! isInBound(returningPlayer->getReturnAccuracy()) )
        {
            std::cout << " out of bounds." << std::endl;
            std::cout << returningPlayer->getName()
                      << " fails to return." << std::endl;

            if(match.getPlayerA() == *returningPlayer)
            {
                match.incPlayerBScore();
            }
            else
            {
                match.incPlayerAScore();
            }

            std::cout << "The score is "
                      << match.getPlayerA().getName()
                      << " "  << match.getPlayerAScore()
                      << ", " << match.getPlayerB().getName()
                      << " "  << match.getPlayerBScore()
                      << "."  << std::endl
                      << std::endl;

            serving = true;
            ++alternatePoints;

            if(alternatePoints == MAX_ALTERNATING_POINTS)
            {
                alternatePoints = 0;
                Player* serv = servingPlayer;

                if(servingPlayer == otherPlayer)
                {
                    servingPlayer = returningPlayer;
                    returningPlayer = serv;
                }
                else
                {
                    servingPlayer = otherPlayer;
                    returningPlayer = serv;
                    otherPlayer = serv;
                }

            }

        }
        else  // in-bounds
        {
            std::cout << " in-bounds." << std::endl;
            serving = false;
            Player* temp = returningPlayer;

            if(returningPlayer == servingPlayer)
            {
                returningPlayer = otherPlayer;
                otherPlayer = temp;
            }
            else
            {
                returningPlayer = servingPlayer;
                otherPlayer = temp;
            }

        }

    }

    // recursive call
    playPoint(match,
              returningPlayer,
              otherPlayer,
              serving,
              alternatePoints,
              servingPlayer);
}

bool Game::isTournamentOver() const
{
    bool over = true;

    for(const auto match: mBracket)
    {

        if(match->isMatchOver())
            over = false;

    }

    return over;
}

bool Game::isInBound(int statistic)
{
    int num = rand() % 100;
    return (statistic > num);
}

double Game::getNrGames() const
{
    return mNrGames;
}

const std::array<Player*, NR_PLAYERS>& Game::getPlayers() const
{
    return mPlayers;
}

const std::array<Match*, NR_GAMES>& Game::getBracket() const
{
    return mBracket;
}

double Game::calculateNrGames(const int nrOfPlayers) const
{

    if(nrOfPlayers < NR_PLAYERS)
    {
        std::string str = boost::lexical_cast<std::string>(nrOfPlayers);
        throw std::invalid_argument("Nr of players [" + str + 
            "] too small.");
    }

    return (boost::math::binomial_coefficient<double>(nrOfPlayers, 2));
}
