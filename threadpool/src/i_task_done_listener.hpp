/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: i_task_done_listener.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_I_TASK_DONE_LISTENER_HPP_
#define THREADPOOL_I_TASK_DONE_LISTENER_HPP_

#include <boost/noncopyable.hpp>

/**
 * A listener who is interested in knowing when its
 * task is done running.
 *
 * @author Rubens Gomes
 */
class ITaskDoneListener: private boost::noncopyable
{
public:
    virtual ~ITaskDoneListener() {};

    /**
     * The client will get a call back on this
     * method when that task is completed.
     */
    virtual void notifyTaskDone() const = 0;
};

#endif /* THREADPOOL_I_TASK_DONE_LISTENER_HPP_ */
