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

#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

#include <stddef.h>

#include "thread_pool.hpp"
#include "task_queue.hpp"

// *static* singleton instance
ThreadPool * ThreadPool::s_instance = NULL;

// *static* singleton instance method
ThreadPool * ThreadPool::instance()
{
    if(ThreadPool::s_instance == NULL)
    {
        ThreadPool::s_instance =
                new ThreadPool(THREAD_POOL_SIZE);
    }

    return ThreadPool::s_instance;
}

// private ctor
ThreadPool::ThreadPool()
:m_total_threads(THREAD_POOL_SIZE),
 m_is_shutdown(false)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPool ["
                             << this
                             << "] constructed";
}

// private dtor
ThreadPool::~ThreadPool()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPool being destructed";
    shutdown();
    BOOST_LOG_TRIVIAL(trace) << "ThreadPool ["
                             <<  this
                             << "] destructed";
}

ThreadPool::ThreadPool(int total_threads)
:m_total_threads(total_threads),
 m_is_shutdown(false)
{
    std::string total =
            boost::lexical_cast<std::string>(total_threads);

    BOOST_LOG_TRIVIAL(trace) << "launching [" + total +
            "] task threads";

    // create and save task thread in vector container.
    for(int i=0; i<m_total_threads; i++)
    {
        std::string indx =
                boost::lexical_cast<std::string>(i);

        TaskThread taskThread;
        // std::vector push_back makes a copy of
        // task thread prior to inserting into the vector.
        BOOST_LOG_TRIVIAL(trace) << "task thread [" +
                indx + "] being pushed to container";
        m_task_threads.push_back(taskThread);
    }

    boost::thread * t = NULL;
    for(std::vector<TaskThread>::size_type i=0;
            i < m_task_threads.size(); i++)
    {
        // create and launch task thread.
        t = new boost::thread(m_task_threads[i]);
        std::string id =
                boost::lexical_cast<std::string>(t->get_id());
        BOOST_LOG_TRIVIAL(trace) << "launched thread id [" + id + "]";
        m_thread_group.add_thread(t);
    }

    BOOST_LOG_TRIVIAL(trace) << "all task threads have been launched.";
}

int ThreadPool::getTotalThreads(void) const
{
    std::string total =
            boost::lexical_cast<std::string>(m_total_threads);
    BOOST_LOG_TRIVIAL(trace) << "total threads [" +
            total + "] in pool";
    return m_total_threads;
}

// synchronized method
void ThreadPool::shutdown(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if(m_is_shutdown)
    {
        BOOST_LOG_TRIVIAL(trace) << "ThreadPool is already down.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "ThreadPool shutdown started";

    for(auto & taskThread : m_task_threads)
    {
        taskThread.stopMe();
    }

    BOOST_LOG_TRIVIAL(trace) <<
            "ThreadPool sending interrupt to all threads";
    m_thread_group.interrupt_all();
    BOOST_LOG_TRIVIAL(trace) << "all threads have stopped.";
    m_is_shutdown = true;
}

void ThreadPool::pushTask(ITask * task)
{
    if(m_is_shutdown)
    {
        throw new std::runtime_error(
                "thread pool has been shutdown.");
    }

    TaskQueue * task_queue = TaskQueue::instance();
    task_queue->push(task);
}

ITask & ThreadPool::popTask(void)
{
    if(m_is_shutdown)
    {
        throw new std::runtime_error(
                "thread pool has been shutdown.");
    }

    TaskQueue * task_queue= TaskQueue::instance();
    ITask & task = task_queue->pop();
    return task;
}
