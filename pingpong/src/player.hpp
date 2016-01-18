//=======================================================================
// Copyright   : Copyright (C) 2016 Rubens S. Gomes 
//=======================================================================

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <string>

/**
 * A class that represents a ping pong player.
 *
 * @author  Rubens Gomes
 */
class Player
{
public:
    /**
     * Specialized constructor to instantiate
     * an immutable instance of the class.
     *
     * @param name the player name
     * @param notes some notes about the player
     * @param returnAccuracy the chance, as a percentage, that the 
     *      player return will be in-bounds.
     * @param returnSkill the chance, as a percentage, that the 
     *      player will successfully return the ball
     * @param returnSpin if game is using spin, subtract this 
     *      player returnSpin
     *      from the opponent returnSkill
     * @param serveAccuracy the chance, as a percentage, that the 
     *      player serve will be in-bounds
     * @param serveSpin if game is using spin, subtract this 
     *      player serveSpin from the opponent returnSkill
     */
    Player(const std::string name,
            const std::string notes,
            const int returnAccuracy,
            const int returnSkill,
            const int returnSpin,
            const int serveAccuracy,
            const int serveSpin);

    ~Player();

    std::string getName() const;
    std::string getNotes() const;
    int getReturnAccuracy() const;
    int getReturnSkill() const;
    int getReturnSpin() const;
    int getServeAccuracy() const;
    int getServeSpin() const;

    int getWins() const;
    void incWins();

    int getLosses() const;
    void incLosses();

    // overload ==/!= operators
    bool operator==(const Player& other) const;
    bool operator!=(const Player& other) const;

private:
    const std::string mName = "";
    const std::string mNotes = "";
    const int mReturnAccuracy = 0;
    const int mReturnSkill = 0;
    const int mReturnSpin = 0;
    const int mServeAccuracy = 0;
    const int mServeSpin = 0;
    int mWins = 0;
    int mLosses = 0;

    Player& operator=(Player const& other) = delete;
};

// overload << operator
std::ostream& operator<<(std::ostream &strm, const Player& player);

#endif /* PLAYER_HPP_ */
