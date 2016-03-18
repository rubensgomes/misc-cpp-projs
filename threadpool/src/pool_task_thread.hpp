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

namespace rg
{
    /**
     * A specialized TaskThread to be used by the Thread Pool
     * policy.  Tasks to be executed by a thread in the pool
     * must be added to the TaskQueue.  Once a task is
     * available in the TaskQueue that task is executed
     * by one of the threads available in the pool.
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

        // copy ctor
        PoolTaskThread(const PoolTaskThread &);

        // dtor
        virtual ~PoolTaskThread();

        /**
         * Pulls and run tasks from the TaskQueue.
         */
        void operator()(void) override;

    private:
        // private copy assignment ctor
        PoolTaskThread & operator=(const PoolTaskThread &);

        // following operators are not used in this class
        bool operator==(const PoolTaskThread &) const;
        bool operator!=(const PoolTaskThread &) const;
    };

}

#endif /* THREADPOOL_POOL_TASK_THREAD_HPP_ */
