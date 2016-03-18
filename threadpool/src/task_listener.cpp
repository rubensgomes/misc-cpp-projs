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

#include "task_listener.hpp"

#include <boost/log/trivial.hpp>

namespace rg
{

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

}
