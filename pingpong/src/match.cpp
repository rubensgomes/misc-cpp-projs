// Copyright (C) 2016 Rubens S. Gomes <rubens.s.gomes@gmail.com>

#include <boost/lexical_cast.hpp>
#include <src/match.hpp>
#include <string>

// overload << operator
std::ostream& operator<<(std::ostream &strm, const Match& match)
{
    std::string str;
    std::ostringstream ss;

    str += match.getPlayerA().getName();
    str += " | ";
    str += match.getPlayerB().getName();
    str += " | ";

    if(match.getWinner() != NULL)
    {
        str += match.getWinner()->getName();
        str += " | ";
    }
    else
    {
        str += "?";
        str += " | ";
    }

    if(match.isMatchOver())
    {
        str += "Over | ";
    }
    else
    {
        str += "Running | ";
    }

    std::string scoreA =
            boost::lexical_cast<std::string>(match.getPlayerAScore());
    std::string scoreB =
            boost::lexical_cast<std::string>(match.getPlayerBScore());

    str += scoreA;
    str += " | ";
    str += scoreB;

    return strm << str;
}


Match::Match(const Player & playerA,
             const Player & playerB)
: mPlayerA(playerA),
  mPlayerB(playerB)
{
    mWinner = NULL;
    mMatchOver = false;
    mPlayerAScore = 0;
    mPlayerBScore = 0;
}

Match::~Match()
{
    delete mWinner;
}

bool Match::isMatchOver() const
{
    bool status = false;

    if( (mPlayerAScore == FINAL_SCORE) ||
        (mPlayerBScore == FINAL_SCORE) )
    {
        status = true;
    }

    return status;
}

void Match::setMatchOver(bool over)
{
    mMatchOver = over;
}

Player & Match::getPlayerA() const
{
    return mPlayerA;
}

Player & Match::getPlayerB() const
{
    return mPlayerB;
}

const Player * Match::getWinner() const
{
    return mWinner;
}

void Match::setWinner(Player & winner)
{
    mWinner = &winner;
}

int Match::getPlayerAScore() const
{
    return mPlayerAScore;
}

void Match::incPlayerAScore()
{
    ++mPlayerAScore;
}

int Match::getPlayerBScore() const
{
    return mPlayerBScore;
}

void Match::incPlayerBScore()
{
    ++mPlayerBScore;
}
