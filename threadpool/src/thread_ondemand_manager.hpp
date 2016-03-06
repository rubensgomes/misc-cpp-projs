/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_ondemand_manager.hpp
 *
 * Date:  March 05, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREAD_ONDEMAND_MANAGER_HPP_
#define THREADPOOL_THREAD_ONDEMAND_MANAGER_HPP_

#include <boost/thread/thread.hpp>
#include <boost/core/noncopyable.hpp>

#include "constants.hpp"
#include "task.hpp"


/**
 * This class implements the OnDemand Thread Policy where
 * a single thread is spawned to execute the given task.
 *
 * @author Rubens Gomes
 */
class ThreadOnDemandManager : private boost::noncopyable
{
public:
    /**
     * Singleton instance method.
     */
    static ThreadOnDemandManager * instance();

    /**
     * Creates and launches a single thread to execute
     * the given task.
     *
     * @param a task to be run by the thread.
     */
    void launchThread(Task *);

    /**
     * Nicely stops the running thread.
     *
     * The user might call this function prior to exiting
     * the application.
     */
    void shutdown(void);

private:
    // private ctor
    ThreadOnDemandManager();

    // dtor is not used in singletons
    ~ThreadOnDemandManager();

    // following operators are not used in singletons
    bool operator==(const ThreadOnDemandManager &) const;
    bool operator!=(const ThreadOnDemandManager &) const;

    bool m_is_shutdown;

    // places threads in both thread group
    // and ptr container
    boost::thread_group m_thread_group;
    boost::ptr_vector<boost::thread> m_threads;

    boost::mutex m_mutex;
    boost::condition_variable m_condition;
    // Singleton
    static ThreadOnDemandManager * s_instance;
};

#endif /* THREADPOOL_THREAD_ONDEMAND_MANAGER_HPP_ */
