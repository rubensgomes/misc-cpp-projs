/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_pool_manager.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREAD_POOL_MANAGER_HPP_
#define THREADPOOL_THREAD_POOL_MANAGER_HPP_

#include "globals.hpp"
#include "task.hpp"

#include <boost/core/noncopyable.hpp>

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

namespace rg
{
    /**
     * This class implements the Thread Pool Pattern.
     *
     * In the class, a number of N threads are created to
     * perform a number of M tasks, organized in a FIFO
     * (First In-First out) queue. Typically, N << M. As
     * soon as a thread completes its task, it will request
     * the next task from the queue until all tasks have been
     * completed. The thread can then terminate, or
     * sleep until there are new tasks available.
     *
     * The number of threads used (N) is a parameter that
     * can be tuned to provide the best performance.
     *
     * The advantage of using a Thread Pool over creating a
     * new thread for each task, is that thread creation
     * and destruction overhead is negated, which may
     * result in better performance and better system
     * stability.
     *
     * @author Rubens Gomes
     */
    class ThreadPoolManager : private boost::noncopyable
    {
    public:
        /**
         * Singleton instance method.
         *
         * When this object is first instantiated it
         * creates a default total number of threads. Then,
         * the threads are placed on stand-by waiting for
         * tasks to be executed.
         */
        static ThreadPoolManager * instance();

        /**
         * Delegates to the TaskQueue to add a
         * task to the task FIFO queue.  This task will
         * be executed by a free thread in the thread pool.
         *
         * @param a task to be run by a thread in the pool.
         * The task ownership is moved to this class
         * instance.
         */
        void pushTask(std::unique_ptr<Task>);

        /**
         * @return the total number of threads in the pool.
         */
        int getTotalThreads(void) const;

        /**
         * Nicely stops all the running threads and shuts down
         * the thread pool  Once the thread pool is shutdown
         * it is no longer available to be used.
         *
         * The user might call this function prior to exiting
         * the application.
         */
        void shutdown(void);

    private:
        // private specialized ctor
        ThreadPoolManager(int total_threads);

        // private ctor
        ThreadPoolManager();

        // private dtor not used in singletons
        ~ThreadPoolManager();

        // private copy ctor
        ThreadPoolManager(const ThreadPoolManager &);

        // private copy assignment ctor
        ThreadPoolManager & operator=(const ThreadPoolManager &);

        // following operators are not used in singletons
        bool operator==(const ThreadPoolManager &) const;
        bool operator!=(const ThreadPoolManager &) const;

        const int m_total_threads;
        bool m_is_shutdown;

        std::vector<std::unique_ptr<std::thread>> m_threads;
        std::mutex m_mutex;
        std::condition_variable m_condition;

        // Singleton
        static ThreadPoolManager * s_instance;
    };
}
#endif /* THREADPOOL_THREAD_POOL_MANAGER_HPP_ */
