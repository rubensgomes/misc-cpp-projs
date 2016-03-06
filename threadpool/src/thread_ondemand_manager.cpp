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

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <boost/log/trivial.hpp>

#include "thread_ondemand_manager.hpp"
#include "ondemand_task_thread.hpp"

// *static* singleton instance
ThreadOnDemandManager * ThreadOnDemandManager::s_instance = NULL;

// *static* singleton instance method
ThreadOnDemandManager * ThreadOnDemandManager::instance()
{
    if(ThreadOnDemandManager::s_instance == NULL)
    {
        ThreadOnDemandManager::s_instance =
                new ThreadOnDemandManager();
    }

    return ThreadOnDemandManager::s_instance;
}

// private ctor
ThreadOnDemandManager::ThreadOnDemandManager()
: m_is_shutdown(false)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager ["
                             << this
                             << "] constructed";
}

// private dtor
ThreadOnDemandManager::~ThreadOnDemandManager()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager being destructed";
    shutdown();
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager ["
                             <<  this
                             << "] destructed";
}

void ThreadOnDemandManager::launchThread(Task * task)
{
    if(task == NULL)
    {
        throw new std::invalid_argument(
                "Invalid argument task: cannot be NULL.");
    }

    OnDemandTaskThread taskThread(task);
    BOOST_LOG_TRIVIAL(trace) << "launching new task thread ...";
    boost::thread * t = new boost::thread(taskThread);
    m_thread_group.add_thread(t);
    m_threads.push_back(t);
}

// synchronized method
void ThreadOnDemandManager::shutdown(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    if(m_is_shutdown)
    {
        BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager is already down.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager shutdown started";

    BOOST_LOG_TRIVIAL(trace) <<
            "ThreadOnDemandManager sending interrupt to all threads";

    m_thread_group.interrupt_all();

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager is sleeping for ["
                             << SHUTDOWN_WAIT_TIME
                             << "] msecs";

    // sleep this thread to give chance for the other
    // running thread to stop.
    boost::this_thread::sleep(
            boost::posix_time::milliseconds(SHUTDOWN_WAIT_TIME));

    BOOST_FOREACH( boost::thread & t, m_threads )
    {
        std::string id =
                boost::lexical_cast<std::string>(t.get_id());

        BOOST_LOG_TRIVIAL (trace) << "thread id ["
                                  << id
                                  << "] detaching...";

        t.detach();

        if(m_thread_group.is_thread_in(&t))
        {
            BOOST_LOG_TRIVIAL (trace) << "thread id ["
                                      << id
                                      << "] being removed from pool.";

            m_thread_group.remove_thread(&t);
        }

    }

    BOOST_LOG_TRIVIAL(trace) << "all threads have stopped.";

    m_is_shutdown = true;
}
