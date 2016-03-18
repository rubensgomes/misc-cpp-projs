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

#include <memory>

namespace rg
{
    /**
     * A specialized TaskThread to be used by the OnDemand
     * Thread policy.  Tasks to be executed by a separate
     * thread must be transfered to the class constructor. The
     * class instance takes ownership of the task which is
     * submitted to run in its own thread.
     *
     * Use the singleton instance of the ThreadOnDemandManager
     * to create/launch/manage the OnDemandTaskThread.
     *
     * @author Rubens Gomes
     */
    class OnDemandTaskThread :  public TaskThread
    {
    public:
        // ctor
        /**
         * @param task to be executed by the thread.  The
         * task ownership is moved to this class instance.
         */
        OnDemandTaskThread(std::unique_ptr<Task>);

        // move ctor
        /**
         * The current OnDemandTaskThread is moved into the
         * newly created/launched thread.
         *
         * @param the OnDemandTaskThread to move into the
         * newly created instance to be run from a separate
         * thread.
         */
        OnDemandTaskThread(OnDemandTaskThread &&);

        // dtor
        virtual ~OnDemandTaskThread();

        /**
         * Callable method to be executed by the launching
         * thread using the on demand thread policy.
         */
        void operator()(void) override;

    private:
        // private ctor
        OnDemandTaskThread();

        // private copy ctor
        OnDemandTaskThread(const OnDemandTaskThread &);

        // private copy assignment ctor
        OnDemandTaskThread & operator=(const OnDemandTaskThread &);

        // following operators are not used in this class
        bool operator==(const OnDemandTaskThread &) const;
        bool operator!=(const OnDemandTaskThread &) const;

        std::unique_ptr<Task> m_task;
    };

    // helper to deep copy unique_ptr
    template< class T >
    std::unique_ptr<T> copy_unique(const std::unique_ptr<T> & rhs)
    {
        return rhs ? std::make_unique<T>( * rhs) : nullptr;
    }

}

#endif /* THREADPOOL_ONDEMAND_TASK_THREAD_HPP_ */
