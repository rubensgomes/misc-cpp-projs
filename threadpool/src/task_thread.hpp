/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_thread.hpp
 *
 * Date:  Jan 16, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_THREAD_HPP_
#define THREADPOOL_TASK_THREAD_HPP_

#include <boost/thread.hpp>

/**
 * This class is a Callable object that is
 * meant to be passed as a calleable function when
 * launching a new thread inside the thread pool.
 *
 * @author Rubens Gomes
 */
class TaskThread
{
public:
    /**
     * Constructor
     */
    TaskThread();

    /**
     * Copy constructor
     *
     * @param the task thread to be cloned.
     */
    TaskThread(const TaskThread &);

    /**
     * Destructor.
     */
    ~TaskThread();

    /**
     * Callable method to be executed by the launching
     * thread in the thread pool.
     */
    void operator()(void);

    /**
     * Sets a flag to prevent this task thread from
     * running.
     */
    void stopMe(void);

    /**
     * @return the running status of this task thread.
     */
    bool isStopped(void) const;

    /**
     * @return my own task thread id
     */
    std::string getThreadId(void) const;

private:
    /**
     * Copy Assignment operator must be made private
     * because we do not want an existing task thread
     * to be re-assigned from another task thread.
     *
     * @param the task thread to be assigned from.
     */
    TaskThread & operator = (const TaskThread &);

    std::string m_thread_id;
    bool m_is_stopped;
    boost::mutex m_mutex;
};

// overload << operator
std::ostream& operator<<(std::ostream &, const TaskThread &);

#endif /* THREADPOOL_TASK_THREAD_HPP_ */
