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

#include "i_task_done_listener.hpp"
#include "i_task.hpp"

#include "task_thread.hpp"
#include "thread_pool.hpp"

// overload << operator
std::ostream& operator<<(std::ostream & strm, const TaskThread & rhs)
{
    return strm << "TaskThread("
                << "stopped ["
                << rhs.isStopped()
                << "])";
}

// ctor
TaskThread::TaskThread()
{
    m_is_stopped = false;
}

// copy ctor
TaskThread::TaskThread(const TaskThread & rhs)
:m_is_stopped(rhs.m_is_stopped),
 m_mutex()
{
    // Notice that the m_mutex is not copyable
    // Therefore a new m_mutex should be used.
}

// dtor
TaskThread::~TaskThread()
{
    BOOST_LOG_TRIVIAL(trace) << "destructing task thread";
    stopMe();
}

// synchronized method
void TaskThread::operator()()
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    ThreadPool * threadPool = ThreadPool::instance();

    while ( ! m_is_stopped )
    {
      // following call blocks on a wait until a task
      // is available.
      ITask * task = threadPool->popTask();
      task->run();

      // notifies its task listener after run is done
      ITaskDoneListener & task_done_listener = task->getNotifier();
      task_done_listener.notifyTaskDone();
    }
}

// synchronized method
void TaskThread::stopMe(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);
    m_is_stopped = true;
}

bool TaskThread::isStopped(void) const
{
    return m_is_stopped;
}
