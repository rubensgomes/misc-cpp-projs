/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: concurrency_strategy.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "concurrency_strategy.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{


ConcurrencyStrategy::~ConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ConcurrencyStrategy ["
                             << this
                             << "] being destructed.";
}

}
