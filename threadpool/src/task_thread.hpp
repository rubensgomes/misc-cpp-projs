/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_thread.hpp
 *
 * Date:  Jan 16, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_THREAD_HPP_
#define THREADPOOL_TASK_THREAD_HPP_

#include <boost/thread.hpp>

/**
 * A Template Method Abstract Base class defining a type
 * to be used by threads that are created using either
 * the OnDemand or Thread Pool strategy.
 *
 * @author Rubens Gomes
 */
class TaskThread
{
public:
    // c-tor
    TaskThread();

    // d-tor
    virtual ~TaskThread() = 0;

    /**
     * Callable method to be executed by the launching
     * thread.
     */
    virtual void operator()(void) = 0;

    /**
     * Attempts to stop this thread.
     */
    virtual void stop(void);

    /**
     * @return the running status of this task thread.
     */
    virtual bool isStopped(void) const;

    /**
     * @return my own task thread id
     */
    virtual std::string getThreadId(void) const;

protected:
    bool m_is_stopped;
    boost::mutex m_mutex;
};

#endif /* THREADPOOL_TASK_THREAD_HPP_ */
