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

#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/thread.hpp>

#include "i_task.hpp"

/**
 * A place holder to manage tasks to be run by the
 * corresponding task thread in the thread pool.
 *
 * NOTE: This class was created to fix circular
 * dependency between TaskThread and ThreadPool.
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
     */
    void push(ITask *);

    /**
     * Pops a task from the queue.  If no task is
     * available this call blocks the current thread
     * by placing the thread on "wait".  The thread
     * is "woken up" once a task is added to the queue
     * via the corresponding push(task) call.
     *
     * @return pops out the next task in the FIFO queue
     * to be executed by a task thread.
     */
    ITask & pop(void);

private:
    TaskQueue();
    ~TaskQueue();

    boost::ptr_vector<ITask> m_tasks;
    boost::mutex m_mutex;
    boost::condition_variable m_condition;
    // Singleton
    static TaskQueue * s_instance;
};

#endif /* THREADPOOL_TASK_QUEUE_HPP_ */
