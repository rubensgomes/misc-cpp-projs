/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_thread.cpp
 *
 * Date:  Jan 16, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include "task_thread.hpp"
#include "utility.hpp"

// c-tor
TaskThread::TaskThread()
: m_is_stopped(false),
  m_mutex()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] constructed.";
}

// private d-tor
TaskThread::~TaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] destructed.";
}

std::string TaskThread::getThreadId(void) const
{
    return Utility::getRunningThreadId();
}

// synchronized method
void TaskThread::stop(void)
{
    if (m_is_stopped)
    {
        BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                                 << getThreadId()
                                 << "] has already been stopped.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                             << getThreadId()
                             << "] is being stopped.";

    m_mutex.lock();
    m_is_stopped = true;
    m_mutex.unlock();
}

bool TaskThread::isStopped(void) const
{
    return m_is_stopped;
}


