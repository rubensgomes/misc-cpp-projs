/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: demand_task_thread.cpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include "demand_task_thread.hpp"

OnDemandTaskThread::OnDemandTaskThread(const ITask & rhs)
: m_task(rhs)
{
    BOOST_LOG_TRIVIAL(trace) << "launching thread";

    // create and launch thread.
    boost::thread t(*this);
}

OnDemandTaskThread::~OnDemandTaskThread()
{
}

void OnDemandTaskThread::operator ()()
{
    // execute the task
    m_task.run();
    // once task is done running notify its listener.
    m_task.getNotifier().notifyTaskDone();
}
