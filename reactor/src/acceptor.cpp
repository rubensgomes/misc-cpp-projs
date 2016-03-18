/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: acceptor.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "acceptor.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

Acceptor::~Acceptor()
{
    BOOST_LOG_TRIVIAL(trace) << "Acceptor ["
                             << this
                             << "] being destructed.";
}

}
