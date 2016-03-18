/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_pool_manager.cpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */

#include "pool_task_thread.hpp"
#include "task_queue.hpp"
#include "thread_pool_manager.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

#include <chrono>
#include <thread>

using namespace std;

namespace rg
{


// static singleton instance
ThreadPoolManager * ThreadPoolManager::s_instance = nullptr;

// static singleton instance method
ThreadPoolManager * ThreadPoolManager::instance()
{
    if(ThreadPoolManager::s_instance == nullptr)
    {
        ThreadPoolManager::s_instance =
                new ThreadPoolManager(THREAD_POOL_SIZE);
    }

    return ThreadPoolManager::s_instance;
}

// private specialized ctor
ThreadPoolManager::ThreadPoolManager(int total_threads)
:m_total_threads(total_threads),
 m_is_shutdown(false),
 m_threads(),
 m_mutex(),
 m_condition()
{
    string total = boost::lexical_cast<string>(total_threads);

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager launching ["
                             << total
                             << "] task threads";

    for(int i=0; i<m_total_threads; i++)
    {
        BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager creating task thread w/index ["
                                 << i
                                 << "]";

        PoolTaskThread poolTaskThread;

        BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager launching new task thread ...";
        unique_ptr<thread> t {new thread(poolTaskThread)};

        string id = boost::lexical_cast<string>(t->get_id());
        BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager launched thread id ["
                                 << id
                                 << "]";

        m_threads.push_back(move(t));
    }
    // poolTaskThread is now destroyed, but the
    // newly-created thread t has a copy, so this is OK

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager all task threads have been launched.";
}

// private dtor
ThreadPoolManager::~ThreadPoolManager()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager ["
                             <<  this
                             << "] being destructed";
}

void ThreadPoolManager::pushTask(unique_ptr<Task> task)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager entering pushTask...";

    if(m_is_shutdown)
    {
        throw new std::runtime_error(
                "thread pool is shutdown.");
    }

    TaskQueue * task_queue = TaskQueue::instance();

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager pushing task to TaskQueue...";

    task_queue->push(move(task));
}

int ThreadPoolManager::getTotalThreads(void) const
{
    string total =
            boost::lexical_cast<string>(m_total_threads);
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager total threads ["
                             << total
                             << "] in pool";

    return m_total_threads;
}

// synchronized
void ThreadPoolManager::shutdown(void)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager entering shutdown...";

    unique_lock<mutex> unq_lock(m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager shutdown started";

    if(m_is_shutdown)
    {
        BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager already down.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager stop all tasks";

    Task::stopAll();

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager shutting down task queue...";

    TaskQueue * queue = TaskQueue::instance();
    queue->shutdown();

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager is now sleeping for ["
                             << SLEEP_WAIT_TIME
                             << "] msecs";

    // sleep this thread to give chance for any other
    // running thread to get started
    chrono::milliseconds duration(SLEEP_WAIT_TIME);
    this_thread::sleep_for(duration);

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager threads should now have stopped.";

    m_is_shutdown = true;
}

}
