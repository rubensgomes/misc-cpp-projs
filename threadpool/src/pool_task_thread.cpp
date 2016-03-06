/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: pool_task_thread.cpp
 *
 * Date:  Mar 3, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

#include "pool_task_thread.hpp"
#include "task_queue.hpp"
#include "utility.hpp"

// c-tor
PoolTaskThread::PoolTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] constructed";
}

// d-tor
PoolTaskThread::~PoolTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] destructed";
}

// copy c-tor
PoolTaskThread::PoolTaskThread(const PoolTaskThread & rhs)
{
    // m_mutex cannot be copied.
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] copied constructed.";
}

// synchronized
void PoolTaskThread::operator()(void)
{
    std::string thread_id = getThreadId();

    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "PoolTaskThread thread id [" +
                thread_id +
                "] has already been stopped.");
    }

    m_mutex.lock();

    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id [" +
            thread_id +
            "] running calleable operator()() ...";

    TaskQueue * task_queue = TaskQueue::instance();

    while ( ! m_is_stopped )
    {
      BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id ["
                               << thread_id
                               << "] pulling task from the queue...";

      try
      {
          // following call blocks on a wait until a task
          // is available.
          Task & task = task_queue->pop();
          BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id ["
                                   << thread_id
                                   << "] running task id ["
                                   << task.getId()
                                   << "]";
          task.run();
          BOOST_LOG_TRIVIAL(trace) << "Task with id ["
                                   << task.getId()
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
    }

    m_mutex.unlock();
}

