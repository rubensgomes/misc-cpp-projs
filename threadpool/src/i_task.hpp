/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: i_task.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_I_TASK_HPP_
#define THREADPOOL_I_TASK_HPP_

#include <boost/noncopyable.hpp>

#include "i_task_done_listener.hpp"

/**
 * A Task contains the code that is to be run from
 * withina separate thread.  Once the task is done
 * executing it notifies its corresponding
 * ITaskDoneListener.
 *
 * @author Rubens Gomes
 */
class ITask : private boost::noncopyable
{
public:
    ITask();
    virtual ~ITask() {};

    /**
     * This method is required by boost::ptr_vector<ITask>
     * when used as a container for ITask pointers.
     *
     * @return a clone instance.
     */
    virtual ITask * clone() const = 0;

    /**
     * The run method should contain the code that is
     * to be executed from within a separate thread.
     */
    virtual void run() const = 0;

    /**
     * @return the corresponding task done listener.
     */
    virtual ITaskDoneListener & getNotifier() const = 0;

    /**
     * Every task is uniquely identified by
     * a unique id.
     *
     * @return my id.
     */
    double getId(void) const;

private:
    double m_id;
    static double s_counter;
};

inline ITask * new_clone(const ITask & rhs)
{
  return rhs.clone();
}

#endif /* THREADPOOL_I_TASK_HPP_ */
