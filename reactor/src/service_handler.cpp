/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: service_handler.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include "service_handler.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

ServiceHandler::~ServiceHandler()
{
    BOOST_LOG_TRIVIAL(trace) << "ServiceHandler ["
                             << this
                             << "] being destructed.";
}

}
