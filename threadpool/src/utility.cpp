/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: utility.cpp
 *
 * Date:  Jan 20, 2016
 * ********************************************************
 */
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>

#include "utility.hpp"

// *static* method
std::string Utility::getRunningThreadId(void)
{
    std::string id =
            boost::lexical_cast<std::string>(boost::this_thread::get_id());
    return id;
}


Utility::Utility()
{
}

Utility::~Utility()
{
}

