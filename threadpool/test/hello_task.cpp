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

#include<thread>

#include <boost/log/trivial.hpp>

#include "globals.hpp"
#include "hello_task.hpp"

using namespace std;

namespace rg
{

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

void HelloTask::do_run() const
{
    BOOST_LOG_TRIVIAL(info) << "HelloTask ["
                            <<  this
                            << "] run started";

    rg::millisecs_t timeout =
            rg::millisecs_t(rg::SLEEP_WAIT_TIME);

    while(! rg::Task::isStopped())
    {
        // create an interrupt point
        this_thread::sleep_for(timeout);
    }

    BOOST_LOG_TRIVIAL(info) << "HelloTask finished.";
}

}
