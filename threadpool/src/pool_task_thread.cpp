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

#include "pool_task_thread.hpp"
#include "task_queue.hpp"
#include "thread_cancellation_exception.hpp"

#include <boost/log/trivial.hpp>

#include <exception>

using namespace std;

namespace rg
{

// ctor
PoolTaskThread::PoolTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] constructed";
}

// copy ctor
PoolTaskThread::PoolTaskThread(const PoolTaskThread & rhs)
: TaskThread(rhs)
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] copied constructed.";
}

// dtor
PoolTaskThread::~PoolTaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread ["
                             << this
                             << "] being destructed";
}

// synchronized
void PoolTaskThread::operator()(void)
{
    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread entering operator() ..";

    unique_lock<mutex> unq_lock(TaskThread::m_mutex);

    string thread_id = getThreadId();

    if( m_is_stopped )
    {
        throw new std::runtime_error(
                "PoolTaskThread thread id [" +
                thread_id +
                "] is stopped.");
    }

    BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id ["
                             << thread_id
                             << "] running operator()() ...";

    TaskQueue * task_queue = TaskQueue::instance();

    while ( ! TaskThread::m_is_stopped )
    {
      BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id ["
                               << thread_id
                               << "] pulling task from queue...";

      unique_ptr<Task> task = nullptr;
      try
      {
          // following call blocks on a wait until a task
          // is available.
          task = move(task_queue->pop());
          BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread id ["
                                   << thread_id
                                   << "] running task id ["
                                   << task->getId()
                                   << "]";

          task->run();

          BOOST_LOG_TRIVIAL(trace) << "PoolTaskThread "
                                   << "Task with id ["
                                   << task->getId()
                                   << "] is done and being destructed";
      }
      catch(const ThreadCancellationException & ex)
      {
          BOOST_LOG_TRIVIAL(info) << "PoolTaskThread ThreadCancellationException ["
                                  << ex.what()
                                  << "].  This thread is now being stopped.";
          unq_lock.unlock();
          TaskThread::stop();
      }
      catch(const runtime_error & ex)
      {
          BOOST_LOG_TRIVIAL(info) << "PoolTaskThread runtime_error ["
                                  << ex.what()
                                  << "].  This thread is now being stopped.";
          unq_lock.unlock();
          TaskThread::stop();
      }
      catch(const exception & ex)
      {
          BOOST_LOG_TRIVIAL(info) << "PoolTaskThread exception ["
                                  << ex.what()
                                  << "].  This thread is now being stopped.";
          unq_lock.unlock();
          TaskThread::stop();
      }
      catch(...)
      {
          BOOST_LOG_TRIVIAL(info) << "PoolTaskThread some error occured."
                                  << " This thread is now being stopped.";
          unq_lock.unlock();
          TaskThread::stop();
      }

    }
}

}
