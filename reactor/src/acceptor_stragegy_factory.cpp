/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: acceptor_strategy_factory.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "acceptor_strategy_factory.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

AcceptorStrategyAbstractFactory::~AcceptorStrategyAbstractFactory()
{
    BOOST_LOG_TRIVIAL(trace) << "AcceptorStrategyAbstractFactory ["
                             << this
                             << "] being destructed.";
}

}
