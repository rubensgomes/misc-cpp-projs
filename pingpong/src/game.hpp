//=======================================================================
// Copyright (C) 2016 Rubens S. Gomes
//=======================================================================

#ifndef GAME_HPP_
#define GAME_HPP_

#include <boost/noncopyable.hpp>

#include <array>
#include <iostream>
#include <string>

#include "match.hpp"
#include "player.hpp"

// columsns found in CSV players data file
const int CSV_COLUMNS = 7;

// serving alternates for points in a row
const int MAX_ALTERNATING_POINTS = 2;

// for simplicity the allowed nr of players and games
const int NR_PLAYERS = 3;
const int NR_GAMES = 3;


/**
 * Singleton used to run the ping pong simulator.
 *
 * @author Rubens Gomes
 */
class Game : private boost::noncopyable
{
public:
    /**
     * Singleton instance method.
     *
     * @param dataFile a CSV file containing players
     * information.
     * @return a singleton instance of this class.
     */
    static Game * instance(const std::string & dataFile);

    /**
     * Run the game, and see outputs displayed on stdout.
     */
    void run();

    /**
     * Checks if there is still any match left.
     *
     * @return true if all matches have been played; false, otherwise.
     */
    bool isTournamentOver() const;

    /**
     * @return the tournament bracket with all matches.
     */
    const std::array<Match *, NR_GAMES> & getBracket() const;

private:
    Game();
    Game(const std::string & dataFile);
    ~Game();

    // (private) ==/!= operators
    bool operator==(const Game& other) const;
    bool operator!=(const Game& other) const;

    // (private) copy constructor and assignment operator
    Game(Game const& other) = delete;
    Game& operator=(Game const& other) = delete;

    void loadPlayersFromCSVFile(const std::string& dataFile);
    void loadBracket();

    void playPoint(Match& match,
                   Player* returningPlayer,
                   Player* otherPlayer,
                   bool serving,
                   int alternatePoints,
                   Player* servingPlayer);

    bool isInBound(int statistic);

    double getNrGames() const;
    const std::array<Player*, NR_PLAYERS>& getPlayers() const;

    double calculateNrGames(const int nrOfPlayers) const;

    double mNrGames = 0;
    std::array<Player*, NR_PLAYERS> mPlayers;
    std::array<Match*, NR_GAMES> mBracket;
    static Game * sInstance; // Singleton
};

// overload << operator
std::ostream& operator<<(std::ostream & strm,
                         const Game & game);

#endif /* GAME_HPP_ */
