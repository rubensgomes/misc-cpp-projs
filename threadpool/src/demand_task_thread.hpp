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
 * This class creates and lauches a thread to
 * execute the given task using the "On Demand
 * Thread Strategy".
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
     * the thread.
     */
    OnDemandTaskThread(const ITask &);

    /**
     * Destructor.
     */
    virtual ~OnDemandTaskThread();

    /**
     * A callable that contains the code to be
     * executed by the thread.  Internally it delegates to
     * the ITask run() method.
     */
    void operator()();

private:
    const ITask & m_task;
};

#endif /* THREADPOOL_DEMAND_TASK_THREAD_HPP_ */
