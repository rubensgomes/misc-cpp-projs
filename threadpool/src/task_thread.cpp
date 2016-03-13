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
#include <thread>

#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

#include "task_thread.hpp"

using namespace std;

// ctor
TaskThread::TaskThread()
: m_is_stopped(false),
  m_mutex()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] constructed.";
}

// private copy ctor
TaskThread::TaskThread(const TaskThread & rhs)
: m_is_stopped(rhs.m_is_stopped),
  m_mutex()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] copy constructed.";
}

// private dtor
TaskThread::~TaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] being destructed.";
}

string TaskThread::getThreadId(void) const
{
    string id = boost::lexical_cast<string>(this_thread::get_id());
    return id;
}

// synchronized
void TaskThread::stop(void)
{
    lock_guard<mutex> lock(m_mutex);

    if (m_is_stopped)
    {
        BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                                 << getThreadId()
                                 << "] already stopped.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                             << getThreadId()
                             << "] stop flag being set.";

    m_is_stopped = true;
}

bool TaskThread::isStopped(void) const
{
    return m_is_stopped;
}


