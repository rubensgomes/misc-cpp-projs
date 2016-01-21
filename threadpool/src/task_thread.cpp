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
: m_thread_id(Utility::getRunningThreadId()),
  m_is_stopped(false),
  m_mutex()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             <<  this
                             << "] with thread id ["
                             << m_thread_id
                             << "] constructed";
}

// copy ctor
TaskThread::TaskThread(const TaskThread & rhs)
:m_thread_id(rhs.m_thread_id),
 m_is_stopped(rhs.m_is_stopped),
 m_mutex()
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
    stopMe();
    BOOST_LOG_TRIVIAL(trace) << "TaskThread ["
                             << this
                             << "] with thread id ["
                             << getThreadId()
                             << "] destructed";
}

// synchronized
void TaskThread::operator()(void)
{
    m_mutex.lock();

    // Since this operator () callable function gets
    // immediatelly invoked by the newly created launching
    // thread, the following id is this actual running task
    // thread
    std::string thread_id = Utility::getRunningThreadId();
    m_thread_id = thread_id;

    BOOST_LOG_TRIVIAL(trace) << "task thread id [" + thread_id +
            "] inside operator()() ...";

    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "task thread id [" + thread_id +
                "] has been stopped.");
    }

    TaskQueue * task_queue = TaskQueue::instance();

    // never ending loop
    while ( ! m_is_stopped )
    {
      BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                               << thread_id
                               << "] pulling task from the queue...";

      try
      {
          // following call blocks on a wait until a task
          // is available.
          ITask & task = task_queue->pop();

          BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                                   << thread_id
                                   << "] running task id ["
                                   << task.getId()
                                   << "]";

          task.run();

          BOOST_LOG_TRIVIAL(trace) << "task with id ["
                                   << task.getId()
                                   << "] is done";

          // notifies its task listener when task is done
          ITaskDoneListener & listener = task.getNotifier();
          listener.notifyTaskDone();

          BOOST_LOG_TRIVIAL(trace) << "task id ["
                                   << task.getId()
                                   << "] notified its listener";

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
    }

    m_mutex.unlock();
}

// synchronized method
void TaskThread::stopMe(void)
{
    if (m_is_stopped)
    {
        BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                                 << getThreadId()
                                 << "] has already been stopped.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "task thread id ["
                             << getThreadId()
                             << "] is being stopped.";

    m_mutex.lock();
    m_is_stopped = true;
    m_mutex.unlock();
}

bool TaskThread::isStopped(void) const
{
    return m_is_stopped;
}

std::string TaskThread::getThreadId(void) const
{
    return m_thread_id;
}
