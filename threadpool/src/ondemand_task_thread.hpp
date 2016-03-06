/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: ondemand_task_thread.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_ONDEMAND_TASK_THREAD_HPP_
#define THREADPOOL_ONDEMAND_TASK_THREAD_HPP_

#include "task.hpp"
#include "task_thread.hpp"


/**
 * A specialized TaskThread to be used by the OnDemand
 * Thread policy.  Tasks to be executed by this thread
 * must be passed into the constructor.  The passed in
 * Task is then executed by a separate task thread.
 *
 * Use the singleton instance of the ThreadOnDemandManager
 * to create/launch/manage the OnDemandTaskThread.
 *
 * @author Rubens Gomes
 */
class OnDemandTaskThread :  public TaskThread
{
public:
    /**
     * c-tor
     *
     * @param task that to be executed by the thread.
     */
    OnDemandTaskThread(Task *);

     // d-tor
    virtual ~OnDemandTaskThread();

    // copy ctor
    OnDemandTaskThread(const OnDemandTaskThread &);

    /**
     * Overridden function.
     *
     * Callable method to be executed by the launching
     * thread using the on demand thread policy.
     */
    virtual void operator()(void);

private:
    // following operators are not used in this class
    bool operator==(const OnDemandTaskThread &) const;
    bool operator!=(const OnDemandTaskThread &) const;

    Task * m_task;
};

#endif /* THREADPOOL_ONDEMAND_TASK_THREAD_HPP_ */
