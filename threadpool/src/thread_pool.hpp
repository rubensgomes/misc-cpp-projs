/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_pool.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREAD_POOL_HPP_
#define THREADPOOL_THREAD_POOL_HPP_

#include <boost/noncopyable.hpp>
#include <boost/thread.hpp>

#include <stack>
#include <vector>

#include "i_task.hpp"
#include "task_thread.hpp"

class TaskThread;

// default number of threads created in the thread pool
// TODO: move this constant to a properties file
const int THREAD_POOL_SIZE = 10;

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
class ThreadPool : private boost::noncopyable
{
    // Singleton
    static ThreadPool * s_instance;

public:
    /**
     * Singleton instance method.
     *
     * When this object is first instantiated it
     * creates a default total number of threads. Then,
     * the threads are placed on stand-by waiting for
     * tasks to be executed.
     */
    static ThreadPool * instance();

    /**
     * Add a task to the task FIFO queue to be executed
     * by a free thread in the thread pool.
     *
     * @param a task to be run by a thread in the pool.
     */
    void pushTask(const ITask &);

    /**
     * A task thread makes a call to this function to
     * extract a task to be run. If there are no tasks
     * to run, the current running thread is placed on
     * "wait"and is "woken up" once a task is added to the queue.
     *
     * @return pops out the next task in the FIFO queue
     * to be executed by a task thread.
     */
    ITask & popTask(void);

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
    ThreadPool(int total_threads);

    // private ctor
    ThreadPool();

    // dtor is not used in singletons
    ~ThreadPool(){};

    // following operators are not used in singletons
    bool operator==(const ThreadPool &) const;
    bool operator!=(const ThreadPool &) const;

    std::stack<ITask> m_tasks;
    std::vector<TaskThread> m_task_threads;

    const int m_total_threads;
    bool m_is_shutdown;

    boost::thread_group m_thread_group;
    boost::mutex m_mutex;
    boost::condition_variable m_condition;
};

#endif /* THREADPOOL_THREAD_POOL_HPP_ */
