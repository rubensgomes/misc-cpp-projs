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

#include <iostream>
#include <exception>

using namespace std;

namespace rg
{

ostream & operator<<(ostream & os, const EventType & type )
{
   switch( type )
   {
      case EventType::ACCEPT_EVENT:
          os << "ACCEPT_EVENT";
          break;
      case EventType::READ_EVENT:
          os << "READ_EVENT";
          break;
      case EventType::WRITE_EVENT:
          os << "WRITE_EVENT";
          break;
      case EventType::TIMEOUT_EVENT:
          os << "TIMEOUT_EVENT";
          break;
      case EventType::SIGNAL_EVENT:
          os << "SIGNAL_EVENT";
          break;
      case EventType::CLOSE_EVENT:
          os << "CLOSE_EVENT";
          break;
      default:
          throw invalid_argument("type is not valid.");
   }

   return os;
}

EventHandler::~EventHandler()
{
    BOOST_LOG_TRIVIAL(trace) << "EventHandler ["
                             << this
                             << "] being destructed.";
}

}
