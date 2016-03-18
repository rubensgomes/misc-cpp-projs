/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: Reactor.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "reactor.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

Reactor::~Reactor()
{
    BOOST_LOG_TRIVIAL(trace) << "Reactor ["
                             << this
                             << "] being destructed.";
}

}
