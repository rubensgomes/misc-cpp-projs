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
#include <boost/chrono.hpp>

#include "ondemand_task_thread.hpp"
#include "utility.hpp"

// ctor
OnDemandTaskThread::OnDemandTaskThread(Task * task)
: m_task(task)
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemnadThread ["
                             << this
                             << "] being constructed.";

    if(task == NULL)
    {
        throw new std::invalid_argument(
                "invalid argument task: cannot be NULL.");
    }

}

// d-tor
OnDemandTaskThread::~OnDemandTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "Demnad thread ["
                             << this
                             << "] destructed.";
}

// copy c-tor
OnDemandTaskThread::OnDemandTaskThread(
        const OnDemandTaskThread & rhs)
: m_task(rhs.m_task)
{
    // m_mutex is not copyable
    BOOST_LOG_TRIVIAL(trace) << "Copy constructed ["
                             << this
                             << "]";
}

void OnDemandTaskThread::operator() (void)
{
    std::string thread_id = Utility::getRunningThreadId();

    BOOST_LOG_TRIVIAL(trace) << "OnDemandTaskThread id [" +
            thread_id +
            "] inside operator()() ...";

    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "OnDemandTaskThread thread id [" +
                thread_id +
                "] has been stopped.");
    }

    m_mutex.lock();

    try
    {
        BOOST_LOG_TRIVIAL(trace) << "OnDemandTaskThread id ["
                                 << thread_id
                                 << "] running task id ["
                                 << m_task->getId()
                                 << "]";
        m_task->run();
        BOOST_LOG_TRIVIAL(trace) << "Task with id ["
                                 << m_task->getId()
                                 << "] is done";
    }
    catch(const boost::thread_interrupted & )
    {
        m_mutex.unlock();
        BOOST_LOG_TRIVIAL(info) << "task thread id ["
                                 << thread_id
                                 << "] interrupted.";
        TaskThread::stop();
    }
    catch(const boost::thread_resource_error &)
    {
        m_mutex.unlock();
        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << thread_id
                                 << "] failed due to resource error";
        TaskThread::stop();
    }
    catch(...)
    {
        m_mutex.unlock();
        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << thread_id
                                 << "] failed due to an error";
        TaskThread::stop();
    }

    m_mutex.unlock();
}

