/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: pool_task_thread.hpp
 *
 * Date:  Mar 3, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_POOL_TASK_THREAD_HPP_
#define THREADPOOL_POOL_TASK_THREAD_HPP_

#include "task_thread.hpp"

/**
 * A specialized TaskThread to be used by the Thread Pool
 * policy.  Tasks to be executed by this thread must be
 * added to the TaskQueue.  Once a task is available in
 * the TaskQueue that task is popped from the queue and
 * executed by this task thread.
 *
 * Use the singleton instance of the ThreadPoolManager to
 * create/launch/manage the PoolTaskThread.
 *
 * @author Rubens Gomes
 */
class PoolTaskThread: public TaskThread
{
public:
    // ctor
    PoolTaskThread();

    // dtor
    virtual ~PoolTaskThread();

    // copy ctor
    PoolTaskThread(const PoolTaskThread &);

    /**
     * Overridden function.
     *
     * Pulls and run tasks from the TaskQueue.
     */
    virtual void operator()(void);

private:
    // following operators are not used in this class
    bool operator==(const PoolTaskThread &) const;
    bool operator!=(const PoolTaskThread &) const;
};

#endif /* THREADPOOL_POOL_TASK_THREAD_HPP_ */
