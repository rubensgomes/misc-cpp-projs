/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_ondemand_manager.cpp
 *
 * Date:  March 05, 2016
 * ********************************************************
 */

#include "thread_ondemand_manager.hpp"
#include "ondemand_task_thread.hpp"

#include <boost/lexical_cast.hpp>
#include <boost/log/trivial.hpp>

#include <stdexcept>

using namespace std;

// *static* singleton instance
ThreadOnDemandManager * ThreadOnDemandManager::s_instance = nullptr;

// *static* singleton instance method
ThreadOnDemandManager * ThreadOnDemandManager::instance(
        unique_ptr<Task> task)
{
    if(ThreadOnDemandManager::s_instance == nullptr)
    {
        ThreadOnDemandManager::s_instance =
                new ThreadOnDemandManager(move(task));
    }

    return ThreadOnDemandManager::s_instance;
}

// private ctor
ThreadOnDemandManager::ThreadOnDemandManager(unique_ptr<Task> task)
: m_is_shutdown(false),
  m_mutex(),
  m_task(move(task))
{
    OnDemandTaskThread taskThread(move(task));
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager launching new task thread ...";
    m_thread = unique_ptr<thread>(new thread(taskThread));
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager thread with id["
                             << m_thread->get_id()
                             << "] launched";

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager ["
                             << this
                             << "] constructed";
}

// private dtor
ThreadOnDemandManager::~ThreadOnDemandManager()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager ["
                             <<  this
                             << "] being destructed";
}

// synchronized
void ThreadOnDemandManager::shutdown(void)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager entering shutdown...";

    lock_guard<mutex> grd_lock(m_mutex);

    if(m_is_shutdown)
    {
        BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager already down.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager calling Task::stopAll()...";

    Task::stopAll();

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager all threads have stopped.";

    m_is_shutdown = true;
}
