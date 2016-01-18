//=======================================================================
// Copyright   : Copyright (C) 2016 Rubens S. Gomes 
//=======================================================================

#ifndef MATCH_HPP_
#define MATCH_HPP_

#include <iostream>

#include "player.hpp"

// final ping pong score points
const int FINAL_SCORE = 11;

// headings for reporting
const char* HEADINGS =
      "PlayerA | PlayerB | Winner | Match Over | A Score | B Score";

/**
 * Class to represent Ping Pong match
 *
 * @author Rubens Gomes
 */
class Match
{
public:
    Match(const Player & playerA,
          const Player & playerB);
    ~Match();

    Player & getPlayerA() const;
    Player & getPlayerB() const;

    bool isMatchOver() const;
    void setMatchOver(bool over);

    const Player* getWinner() const;
    void setWinner(Player& winner);

    int getPlayerAScore() const;
    void incPlayerAScore();

    int getPlayerBScore() const;
    void incPlayerBScore();

private:

    // (private) ==/!= operators
    bool operator==(const Match& other) const;
    bool operator!=(const Match& other) const;

    // (private) copy constructor and assignment operator
    Match(Match const& other);
    Match& operator=(Match const& other);

    const Player mPlayerA;
    const Player mPlayerB;

    Player* mWinner;
    bool mMatchOver;
    int mPlayerAScore;
    int mPlayerBScore;
};

// overload << operator
std::ostream& operator<<(std::ostream &strm, const Match& match);

#endif /* MATCH_HPP_ */
