/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: hello_task.cpp
 *
 * Date:  Jan 21, 2016
 * ********************************************************
 */

#include <boost/log/trivial.hpp>
#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "constants.hpp"
#include "hello_task.hpp"


// ctor
HelloTask::HelloTask()
{
    BOOST_LOG_TRIVIAL(trace) << "HelloTask ["
                             <<  this
                             << "] constructed";
}

// dtor
HelloTask::~HelloTask()
{
    BOOST_LOG_TRIVIAL(trace) << "HelloTask ["
                             <<  this
                             << "] destructed";
}

// clone
Task * HelloTask::clone(void) const
{
    BOOST_LOG_TRIVIAL(trace) << "HelloTask ["
                             <<  this
                             << "] is being cloned";

    HelloTask * t = new HelloTask();
    return t;
}

void HelloTask::do_run() const
{
    BOOST_LOG_TRIVIAL(info) << "HelloTask ["
                            <<  this
                            << "] Hello World!";

    BOOST_LOG_TRIVIAL(info) << "Entering forever loop.";

    while(true)
    {
        // create an interrupt point
        boost::this_thread::sleep_for(
          boost::chrono::milliseconds{SLEEP_WAIT_TIME});
        ;
    }

    BOOST_LOG_TRIVIAL(info) << "Leaving forever loop.";
}
