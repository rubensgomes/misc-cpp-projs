/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: demand_task_thread.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_DEMAND_TASK_THREAD_HPP_
#define THREADPOOL_DEMAND_TASK_THREAD_HPP_

#include <boost/thread.hpp>

#include "i_task.hpp"


/**
 * This class is a Callable whose operator() is meant
 * to be passed as a Calleable to run from a thread
 * using the "On Demand Thread Strategy".
 *
 * @author Rubens Gomes
 */
class OnDemandTaskThread
{
public:
    /**
     * Constructor
     *
     * @param task that contains code to be executed by
     * the calling thread.
     */
    OnDemandTaskThread(const ITask &);

    /**
     * Destructor.
     */
    virtual ~OnDemandTaskThread();

    /**
     * This method implements the code that is to be
     * executed by the calling a thread.
     *
     * Internally it calls the ITask run() method.
     */
    void operator()();

    /**
     * This method sets a flag in the object to prevent
     * the thread from running.  This method uses
     * synchronization to ensure the instance stop flag
     * is changed as an atomic operation.
     */
    void stopMe();

private:
    const ITask & m_task;
    bool m_stop_me;
    boost::mutex m_mutex;
};

#endif /* THREADPOOL_DEMAND_TASK_THREAD_HPP_ */
