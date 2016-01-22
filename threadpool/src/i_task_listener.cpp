/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: i_task_listener.cpp
 *
 * Date:  Jan 22, 2016
 * ********************************************************
 */

#include "i_task_listener.hpp"

bool ITaskListener::operator==(const ITaskListener & rhs) const
{
    bool status = (this == &rhs);
    return status;
}

bool ITaskListener::operator!=(const ITaskListener & rhs) const
{
    bool status = !(this == &rhs);
    return status;
}
