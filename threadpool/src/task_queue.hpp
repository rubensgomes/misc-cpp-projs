/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_queue.hpp
 *
 * Date:  Jan 19, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_QUEUE_HPP_
#define THREADPOOL_TASK_QUEUE_HPP_

#include "globals.hpp"
#include "task.hpp"
#include "thread_cancellation_point.hpp"

#include <boost/noncopyable.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>


namespace rg
{
    /**
     * A place holder to manage tasks to be
     * run by the corresponding task thread in
     * the thread pool.
     *
     * NOTE: This class was created to fix a
     * circular dependency that existed between
     * TaskThread and ThreadPool.
     *
     * @author Rubens Gomes
     */
    class TaskQueue : private boost::noncopyable
    {
    public:
        /**
         * Singleton instance method.
         */
        static TaskQueue * instance();

        /**
         * Add a task to the task FIFO queue.  Once a task
         * is called it calls notify_all to unblock any thread
         * that is pending on a task to be available.
         *
         * @param a task to be run by a thread in the pool.
         * The task ownership is moved to the queue.
         */
        void push(std::unique_ptr<Task>);

        /**
         * Pops a task from the queue.  If no task is
         * available this call blocks the current thread
         * by placing the thread on "wait".  The thread
         * is "woken up" once a task is added to the queue
         * via the corresponding push(task) call.
         * <p>
         * ATTENTION:  This function will raise an exception
         * when the TaskQueue is shutdown.  The user should
         * have a try ... catch block around this function
         * if handling the exception is necessary.
         * <p>
         * @return pops out the next task in the FIFO queue
         * to be executed by a task thread.
         */
        std::unique_ptr<Task> pop(void);

        /**
         * Shuts down the queue by completely clearing
         * all the tasks stored in the queue.
         */
        void shutdown(void);

    private:
        // private ctor
        TaskQueue();

        // private copy ctor
        TaskQueue(const TaskQueue &);

        // private dtor
        ~TaskQueue();

        // private copy assignment ctor
        TaskQueue & operator=(const TaskQueue &);

        // following operators are not used in this class
        bool operator==(const TaskQueue &) const;
        bool operator!=(const TaskQueue &) const;

        bool m_is_stopped;
        std::queue<std::unique_ptr<Task>> m_tasks;
        std::mutex m_mutex;
        std::condition_variable m_condition;
        ThreadCancellationPoint m_cancel_point;

        // Singleton
        static TaskQueue * s_instance;
        static millisecs_t s_timeout;
    };
}

#endif /* THREADPOOL_TASK_QUEUE_HPP_ */
