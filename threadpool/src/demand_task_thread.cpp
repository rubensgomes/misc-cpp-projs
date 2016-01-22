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
#include "utility.hpp"

// ctor
OnDemandTaskThread::OnDemandTaskThread(const ITask & task)
: m_task(task),
  m_is_stopped(false)
{
    BOOST_LOG_TRIVIAL(trace) << "Demnad thread ["
                             << this
                             << "] constructed.";

    // create / launch and store thread in group.
    m_thread = new boost::thread(*this);
    m_thread_group.add_thread(m_thread);
}

// copy ctor
OnDemandTaskThread::OnDemandTaskThread(const OnDemandTaskThread & rhs)
:m_task(rhs.m_task),
 m_thread_group(),
 m_thread(),
 m_thread_id(rhs.m_thread_id),
 m_is_stopped(rhs.m_is_stopped),
 m_mutex()
{
    // Notice that the m_thread, m_thread_group and
    // m_mutex are not copyable.

    BOOST_LOG_TRIVIAL(trace) << "Thread ["
                             <<  this
                             << "] copy constructed";
}

OnDemandTaskThread::~OnDemandTaskThread()
{
    stopMe();

    BOOST_LOG_TRIVIAL(trace) << "Demnad thread ["
                             << this
                             << "] destructed.";
}

void OnDemandTaskThread::operator ()(void)
{
    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "thread has been stopped.");
    }

    m_mutex.lock();

    // Since this operator () callable function gets
    // immediatelly invoked by the newly created launching
    // thread, the following id is this actual running task
    // thread
    std::string thread_id = Utility::getRunningThreadId();
    m_thread_id = thread_id;

    BOOST_LOG_TRIVIAL(trace) << "Demnad thread id ["
                             << m_thread_id
                             << "] is now running task.";

    try
    {
        // execute the task. If this call blocks, it will
        // be interrupted by calling the stopMe() method.
        m_task.run();

        BOOST_LOG_TRIVIAL(trace) << "Task of demnad thread id ["
                                 << m_thread_id
                                 << "] is now done.";

        m_is_stopped = true;
    }
    catch(const boost::thread_interrupted & )
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(info) << "task thread id ["
                                 << thread_id
                                 << "] interrupted.";
        stopMe();
    }
    catch(const boost::thread_resource_error &)
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << m_thread_id
                                 << "] failed due to resource error";
    }
    catch(...)
    {
        m_mutex.unlock();

        BOOST_LOG_TRIVIAL(error) << "thread with id [ "
                                 << m_thread_id
                                 << "] failed due to an error";
    }

    m_is_stopped = true;
    m_mutex.unlock();
}

void OnDemandTaskThread::stopMe(void)
{
    if( m_is_stopped)
    {
        return;
    }

    m_mutex.lock();

    BOOST_LOG_TRIVIAL(trace) <<
            "Sending interrupt to running thread";

    m_thread_group.interrupt_all();

    BOOST_LOG_TRIVIAL(trace) << "Thread is sleeping for ["
                             << STOP_WAIT_TIME
                             << "] msecs";

    // sleep this thread to give chance for the other
    // running thread to stop.
    boost::this_thread::sleep(
            boost::posix_time::milliseconds(STOP_WAIT_TIME));

    BOOST_LOG_TRIVIAL (trace) << "thread id ["
                              << m_thread_id
                              << "] detaching...";

    m_thread->detach();

    if(m_thread_group.is_thread_in(m_thread))
    {
        BOOST_LOG_TRIVIAL (trace) << "thread id ["
                                  << m_thread_id
                                  << "] being removed from thread group.";

        m_thread_group.remove_thread(m_thread);
    }

    BOOST_LOG_TRIVIAL(trace) << "thread has stopped.";

    m_is_stopped = true;
    m_mutex.unlock();
}
