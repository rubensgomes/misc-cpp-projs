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

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include <boost/core/noncopyable.hpp>

#include "globals.hpp"
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
     * @param a task to be run by the thread. The task
     * ownership is moved to this class instance.
     */
    void launchThread(std::unique_ptr<Task>);

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

    // private dtor
    ~ThreadOnDemandManager();

    // private copy ctor
    ThreadOnDemandManager(const ThreadOnDemandManager &);

    // private copy assignment
    ThreadOnDemandManager & operator=(const ThreadOnDemandManager &);

    // following operators are not used in singletons
    bool operator==(const ThreadOnDemandManager &) const;
    bool operator!=(const ThreadOnDemandManager &) const;

    bool m_is_shutdown;
    std::mutex m_mutex;

    // Singleton
    static ThreadOnDemandManager * s_instance;
};

#endif /* THREADPOOL_THREAD_ONDEMAND_MANAGER_HPP_ */
