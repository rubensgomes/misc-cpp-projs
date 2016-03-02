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

#include "demand_task_thread.hpp"
#include "utility.hpp"

// ctor
OnDemandTaskThread::OnDemandTaskThread(const ITask & task)
: m_task(task),
  m_is_stopped( false )
{
    BOOST_LOG_TRIVIAL(trace) << "Demnad thread ["
                             << this
                             << "] being constructed.";

    // create / launch thread.
    BOOST_LOG_TRIVIAL(trace) << "Spawning new Demnad thread";

    m_thread = new boost::thread(*this);
}

// copy ctor
OnDemandTaskThread::OnDemandTaskThread(const OnDemandTaskThread & rhs)
:m_task(rhs.m_task),
 m_is_stopped(rhs.m_is_stopped),
 m_thread(),
 m_mutex()
{
    // Notice that m_thread m_mutex are not copyable.

    BOOST_LOG_TRIVIAL(trace) << "Thread ["
                             <<  this
                             << "] copy constructed";
}

OnDemandTaskThread::~OnDemandTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "Demnad thread ["
                             << this
                             << "] destructed.";
}

void OnDemandTaskThread::join(void)
{
    if(m_thread != NULL)
    {
        BOOST_LOG_TRIVIAL(trace) << "joining with newly created thread ";
        m_thread->join();
    }
}

void OnDemandTaskThread::operator ()(void)
{
    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "thread has already been stopped.");
    }

    m_mutex.lock();

    // Since this operator () callable function gets
    // immediatelly invoked by the newly created launching
    // thread, the following id is this actual running task
    // thread
    std::string thread_id = Utility::getRunningThreadId();

    BOOST_LOG_TRIVIAL(trace) << "Demnad thread id ["
                             << thread_id
                             << "] is now executinga a task.";

    try
    {
        // execute the task. If this call blocks, and it
        // provides an interrupt point (calling wait) it will
        // be interrupted by calling the stopMe() method.
        m_task.run();

        BOOST_LOG_TRIVIAL(trace) << "Task of demnad thread id ["
                                 << thread_id
                                 << "] is now done.";

        m_is_stopped = true;
    }
    catch(const boost::thread_interrupted & )
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(info) << "task thread id ["
                                 << thread_id
                                 << "] interrupted.";
        stop();
    }
    catch(const boost::thread_resource_error &)
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << thread_id
                                 << "] failed due to resource error";
    }
    catch(...)
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << thread_id
                                 << "] failed due to an error";
    }

    m_is_stopped = true;
    m_mutex.unlock();
}

void OnDemandTaskThread::sleep(int msecs)
{
    if(msecs <=0)
    {
        throw new std::runtime_error(
                "msecs cannot be 0 or negative.");
    }

    BOOST_LOG_TRIVIAL(trace) << "sleeping for ["
                             << msecs
                             << "] msecs";

    boost::this_thread::sleep_for(
      boost::chrono::milliseconds{msecs});
}

void OnDemandTaskThread::stop(void)
{
    if( m_is_stopped)
    {
        return;
    }

    m_mutex.lock();

    if(m_thread != NULL)
    {
        BOOST_LOG_TRIVIAL(trace) <<
                "Sending interrupt to running thread";

        m_thread->interrupt();
    }

    BOOST_LOG_TRIVIAL(trace) << "Thread is sleeping for ["
                             << STOP_WAIT_TIME
                             << "] msecs";

    // sleep this thread to give chance for the other
    // running thread to stop.
    boost::this_thread::sleep(
            boost::posix_time::milliseconds(STOP_WAIT_TIME));

    BOOST_LOG_TRIVIAL(trace) << "thread has stopped.";

    m_is_stopped = true;
    m_mutex.unlock();
}
