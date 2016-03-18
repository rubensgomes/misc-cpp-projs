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

#include "ondemand_task_thread.hpp"
#include "thread_cancellation_exception.hpp"

#include <boost/log/trivial.hpp>

using namespace std;

namespace rg
{

// ctor
OnDemandTaskThread::OnDemandTaskThread(std::unique_ptr<Task> task)
: m_task(move(task))
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread ["
                             << this
                             << "] Task ["
                             << this->m_task.get()
                             << "] constructed.";
}

// move ctor
OnDemandTaskThread::OnDemandTaskThread(OnDemandTaskThread && rhs)
: m_task(move(rhs.m_task))
{
    // m_mutex is not moveable
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread move constructed ["
                             << this
                             << "] Task ["
                             << this->m_task.get()
                             << "]";
}

// dtor
OnDemandTaskThread::~OnDemandTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread ["
                             << this
                             << "] Task ["
                             << this->m_task.get()
                             << "] being destructed.";
}

// synchronized
void OnDemandTaskThread::operator() (void)
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread ["
                             << this
                             << "] entering operator() ..";

    lock_guard<mutex> grd_lock(TaskThread::m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread ["
                             << this
                             << "] requesting thread id...";


    string thread_id = getThreadId();

    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread thread id ["
                             << thread_id
                             << "] inside operator()() ...";

    if( TaskThread::m_is_stopped )
    {
        throw new runtime_error(
                "OnDemandTaskThread thread id [" +
                thread_id +
                "] is stopped.");
    }

    BOOST_LOG_TRIVIAL(trace) << "OnDemandTaskThread id ["
                             << thread_id
                             << "] running task id ["
                             << m_task->getId()
                             << "]";
    m_task->run();
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadTaskThread "
                             << "Task with id ["
                             << m_task->getId()
                             << "] is done";
}

}
