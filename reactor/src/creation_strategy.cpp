/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: creation_strategy.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "creation_strategy.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

CreationStrategy::~CreationStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "CreationStrategy ["
                             << this
                             << "] being destructed.";
}

}
