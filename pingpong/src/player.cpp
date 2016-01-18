// Copyright (C) 2016 Rubens S. Gomes <rubens.s.gomes@gmail.com>

#include "player.hpp"

// overload << operator
std::ostream& operator<<(std::ostream &strm, const Player & rhs)
{
    return strm << "Player("
            << "name["
            << rhs.getName()
            << "], notes["
            << rhs.getNotes()
            << "], returnAccuracy["
            << rhs.getReturnAccuracy()
            << "], returnSkill["
            << rhs.getReturnSkill()
            << "], returnSpin["
            << rhs.getReturnSpin()
            << "], serverAccuracy["
            << rhs.getServeAccuracy()
            << "], serverSpin["
            << rhs.getServeSpin()
            << "])";
}

// specialized constructor
Player::Player(const std::string name,
        const std::string notes,
        const int returnAccuracy,
        const int returnSkill,
        const int returnSpin,
        const int serveAccuracy,
        const int serveSpin)
: mName(name),
  mNotes(notes),
  mReturnAccuracy(returnAccuracy),
  mReturnSkill(returnSkill),
  mReturnSpin(returnSpin),
  mServeAccuracy(serveAccuracy),
  mServeSpin(serveSpin) {}

// Destructor
Player::~Player(){}

// overload equal operator
bool Player::operator==(const Player& rhs) const
{
    return (rhs.getName() == this->getName());
}

// overload not equal operator
bool Player::operator!=(const Player& rhs) const
{
    return ! (rhs == *this);
}

std::string Player::getName() const
{
    return mName;
}

std::string Player::getNotes() const
{
    return mNotes;
}

int Player::getReturnAccuracy() const
{
    return mReturnAccuracy;
}

int Player::getReturnSkill() const
{
    return mReturnSkill;
}

int Player::getReturnSpin() const
{
    return mReturnSpin;
}

int Player::getServeAccuracy() const
{
    return mServeAccuracy;
}

int Player::getServeSpin() const
{
    return mServeSpin;
}

int Player::getLosses() const
{
    return mLosses;
}

void Player::incLosses()
{
    ++mLosses;
}

int Player::getWins() const
{
    return mWins;
}

void Player::incWins()
{
    ++mWins;
}
