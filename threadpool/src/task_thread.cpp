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
#include <boost/lexical_cast.hpp>

#include "i_task_done_listener.hpp"
#include "i_task.hpp"

#include "task_thread.hpp"
#include "task_queue.hpp"
#include "utility.hpp"

// overload << operator
std::ostream& operator<<(std::ostream & strm,
                         const TaskThread & rhs)
{
    return strm << "TaskThread( stopped ["
                << rhs.isStopped()
                << "])";
}

// ctor
TaskThread::TaskThread()
{
    m_is_stopped = false;
    m_thread_id = Utility::getRunningThreadId();
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             <<  this
                             << "] with thread id ["
                             << m_thread_id
                             << "] constructed";
}

// copy ctor
TaskThread::TaskThread(const TaskThread & rhs)
:m_is_stopped(rhs.m_is_stopped),
 m_mutex(),
 m_thread_id(rhs.m_thread_id)
{
    // Notice that the m_mutex is not copyable
    // Therefore a new m_mutex should be used.
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             <<  this
                             << "] with thread id ["
                             << m_thread_id
                             << "] copy ctor'ed from rhs with thread id ["
                             << rhs.getThreadId()
                             << "]";
}

// dtor
TaskThread::~TaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] with thread id ["
                             << getThreadId()
                             << "] destructed";
}

void TaskThread::operator()(void)
{
    // Since this operator () callable function gets
    // immediatelly invoked by the newly created launching
    // thread, the following id is this actual running task
    // thread
    std::string thread_id = Utility::getRunningThreadId();
    m_thread_id = thread_id;
    BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id +
            "] found inside operator()() function...";

    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "task thread id [" + thread_id +
                "] has been stopped.");
    }

    TaskQueue * task_queue = TaskQueue::instance();

    while ( ! m_is_stopped )
    {
      // following call blocks on a wait until a task
      // is available.
      BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id +
              "] pulling task from the queue...";
      ITask & task = task_queue->pop();
      BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id + "] is running";
      task.run();

      BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id +
              "] is done";
      // notifies its task listener after run is done
      ITaskDoneListener & listener = task.getNotifier();
      listener.notifyTaskDone();
      BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id +
              "] notified its listener";
    }

    if( m_is_stopped )
    {
        throw new std::runtime_error("task thread id [" +
                thread_id + "] was stopped.");
    }

}

// synchronized method
void TaskThread::stopMe(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                             << getThreadId()
                             << "] is being stopped.";
    m_is_stopped = true;
}

bool TaskThread::isStopped(void) const
{
    return m_is_stopped;
}

std::string TaskThread::getThreadId(void) const
{
    return m_thread_id;
}
