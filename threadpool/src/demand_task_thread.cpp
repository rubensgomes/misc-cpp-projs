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

#include "demand_task_thread.hpp"

OnDemandTaskThread::OnDemandTaskThread(const ITask & rhs)
: m_task(rhs)
{
    m_stop_me = false;
}

OnDemandTaskThread::~OnDemandTaskThread()
{
    m_stop_me = true;
}

void OnDemandTaskThread::operator ()()
{

    if( ! m_stop_me )
    {
        // execute the task
        m_task.run();

        // once task is done running notify its listener.
        m_task.getNotifier().notifyTaskDone();
    }

}

// synchronized method
void OnDemandTaskThread::stopMe()
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_stop_me = true;
}
