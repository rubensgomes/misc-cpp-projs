/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: HelloTask.cpp
 *
 * Date:  Jan 21, 2016
 * ********************************************************
 */

#include <boost/log/trivial.hpp>

#include "hello_task.hpp"

// ctor
HelloTask::HelloTask()
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] constructed";
}

// dtor
HelloTask::~HelloTask()
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] destructed";
}

// clone
ITask * HelloTask::clone(void) const
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] is being cloned";

    HelloTask * t = new HelloTask();
    return t;
}

void HelloTask::do_run() const
{
    BOOST_LOG_TRIVIAL(info) << "Task ["
                             <<  this
                             << "] Hello World!";

}
