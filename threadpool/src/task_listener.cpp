/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_listener.cpp
 *
 * Date:  Jan 22, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include "task_listener.hpp"

TaskListener::~TaskListener()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskListener ["
                             << this
                             << "] is being destructed.";
}

bool TaskListener::operator==(const TaskListener & rhs) const
{
    BOOST_LOG_TRIVIAL(trace) << "TaskListener ["
                             << this
                             << "] == comparison.";

    bool status = (this == &rhs);
    return status;
}

bool TaskListener::operator!=(const TaskListener & rhs) const
{
    BOOST_LOG_TRIVIAL(trace) << "TaskListener ["
                             << this
                             << "] != comparison.";

    bool status = !(this == &rhs);
    return status;
}
