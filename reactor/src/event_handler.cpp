/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: EventHandler.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "event_handler.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

EventHandler::~EventHandler()
{
    BOOST_LOG_TRIVIAL(trace) << "EventHandler ["
                             << this
                             << "] being destructed.";
}

}
