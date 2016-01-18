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

#include "i_task_done_listener.hpp"


/**
 * A Task contains the code that is to be run from
 * withina separate thread.  Once the task is done
 * executing it notifies its corresponding
 * ITaskDoneListener.
 *
 * @author Rubens Gomes
 */
class ITask
{
public:
    virtual ~ITask() {};

    /**
     * The run method should contain the code that is
     * to be executed from within a separate thread.
     */
    virtual void run() const = 0;

    /**
     * @return the corresponding task done listener.
     */
    virtual ITaskDoneListener & getNotifier() const = 0;
};
#endif /* THREADPOOL_I_TASK_HPP_ */
