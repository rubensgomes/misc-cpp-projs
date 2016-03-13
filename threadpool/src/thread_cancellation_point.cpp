/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_cancellation_point.cpp
 *
 * Date:  Mar 9, 2016
 * ********************************************************
 */

#include <boost/log/trivial.hpp>

#include "thread_cancellation_exception.hpp"
#include "thread_cancellation_point.hpp"

using namespace std;

// ctor
ThreadCancellationPoint::ThreadCancellationPoint()
: m_is_stopped(false),
  m_mutex(),
  m_condition()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint ["
                             << this
                             << "] constructed.";
}

// copy ctor
ThreadCancellationPoint::ThreadCancellationPoint(
            const ThreadCancellationPoint & rhs)
: m_is_stopped(rhs.m_is_stopped),
  m_mutex(),
  m_condition()
{
    // cannot copy mutex and condition variable
    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint ["
                             << this
                             << "] copy constructed.";
}

// dtor
ThreadCancellationPoint::~ThreadCancellationPoint()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint ["
                             << this
                             << "] being destructed.";
}

// synchronized
void ThreadCancellationPoint::wait(
        const millisecs_t & timeout)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint entering wait...";

    unique_lock<mutex> unq_lock(m_mutex);

    if( m_is_stopped ||
        (m_condition.wait_for(unq_lock, timeout) == cv_status::no_timeout) )
    {
        if(m_is_stopped)
        {
            m_is_stopped = false;
            throw new ThreadCancellationException(
                 "thread cancellation stop has been called.");
        }

        m_is_stopped = false;
        throw new ThreadCancellationException(
             "thread cancellation wait called with no timeout.");
    }
}

// synchronized
void ThreadCancellationPoint::stop(void)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint entering stop...";

    unique_lock<mutex> lock(m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "ThreadCancellationPoint stop called.";

    m_is_stopped = true;
    m_condition.notify_all();
}
