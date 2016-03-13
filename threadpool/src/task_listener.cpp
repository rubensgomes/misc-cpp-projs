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

TaskListener::~TaskListener()
{}

bool TaskListener::operator==(const TaskListener & rhs) const
{
    bool status = (this == &rhs);
    return status;
}

bool TaskListener::operator!=(const TaskListener & rhs) const
{
    bool status = !(this == &rhs);
    return status;
}
