/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_pool.cpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */


#include <boost/log/trivial.hpp>

#include <stddef.h>
#include <sstream>

#include "thread_pool.hpp"

// singleton static instance
ThreadPool* ThreadPool::s_instance = NULL;

// singleton instance method
ThreadPool* ThreadPool::instance()
{
    if(s_instance == NULL)
    {
        s_instance = new ThreadPool(THREAD_POOL_SIZE);
    }

    return s_instance;
}

ThreadPool::ThreadPool()
:m_total_threads(THREAD_POOL_SIZE)
{
    m_is_shutdown = false;
}

ThreadPool::ThreadPool(int total_threads)
:m_total_threads(total_threads),
 m_is_shutdown(false)
{
    std::string msg;
    std::stringstream ss;
    ss << "launching [" <<  total_threads
       << "] task threads...";
    msg = ss.str();

    BOOST_LOG_TRIVIAL(trace) << msg;

    // create and save task thread in vector container.
    for(int i=0; i<m_total_threads; i++)
    {
        TaskThread taskThread;
        // std::vector push_back makes a copy of
        // task thread prior to inserting into the vector.
        m_task_threads.push_back(taskThread);
    }

    boost::thread * t = NULL;
    for(std::vector<TaskThread>::size_type i=0;
            i < m_task_threads.size(); i++)
    {
        // create and launch task thread.
        t = new boost::thread(m_task_threads[i]);
        m_thread_group.add_thread(t);
    }

    BOOST_LOG_TRIVIAL(trace) << "all task threads have been launched.";
}

int ThreadPool::getTotalThreads(void) const
{
    return m_total_threads;
}

// synchronized method
void ThreadPool::shutdown(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if(m_is_shutdown)
    {
        throw new std::runtime_error("thread pool has already been shutdown.");
    }

    BOOST_LOG_TRIVIAL(trace) << "stopping all threads...";

    // TODO: not clear about following algorithm
    for(auto & taskThread : m_task_threads)
    {
        taskThread.stopMe();
    }

    m_is_shutdown = true;
    BOOST_LOG_TRIVIAL(trace) << "all threads have stopped.";
}

// synchronized method
void ThreadPool::pushTask(ITask * task)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if(m_is_shutdown)
    {
        throw new std::runtime_error("thread pool has been shutdown.");
    }

    BOOST_LOG_TRIVIAL(trace) << "pushing task to queue";
    m_tasks.push_back(task);
    m_condition.notify_all();
}

// synchronized method
ITask & ThreadPool::popTask(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if(m_is_shutdown)
    {
        throw new std::runtime_error("thread pool has been shutdown.");
    }

    BOOST_LOG_TRIVIAL(trace) << "checking if task queue is empty";
    while(m_tasks.empty())
    {
        // Notice that the lock is passed to wait: wait
        // will atomically add the thread to the set of
        // threads waiting on the condition variable,
        // and unlock the m_mutex. When the thread is woken,
        // the m_mutex will be locked again before the call
        // to wait returns. This allows other threads to
        // acquire the m_mutex in order to update the
        // shared data, and ensures that the data associated
        // with the condition is correctly synchronized.
        m_condition.wait(lock);
    }

    BOOST_LOG_TRIVIAL(trace) << "popping task from queue";
    ITask & task = m_tasks.front();
    return task;
}
