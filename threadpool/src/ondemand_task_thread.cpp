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

// ctor
OnDemandTaskThread::OnDemandTaskThread(std::unique_ptr<Task> task)
: m_task(move(task))
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread ["
                             << this
                             << "] constructed.";
}

// copy ctor
OnDemandTaskThread::OnDemandTaskThread(const OnDemandTaskThread & rhs)
: TaskThread(rhs),
  m_task(rhs.m_task->clone())
{
    // m_mutex is not copyable
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread copy constructed ["
                             << this
                             << "]";
}

// dtor
OnDemandTaskThread::~OnDemandTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread ["
                             << this
                             << "] being destructed.";
}

// synchronized
void OnDemandTaskThread::operator() (void)
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread entering operator() ..";

    lock_guard<mutex> grd_lock(TaskThread::m_mutex);

    string thread_id = TaskThread::getThreadId();

    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread id ["
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
    BOOST_LOG_TRIVIAL(trace) << "OnDemandTaskThread "
                             << "Task with id ["
                             << m_task->getId()
                             << "] is done";
}

