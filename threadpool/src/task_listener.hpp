/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_done_listener.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_DONE_LISTENER_HPP_
#define THREADPOOL_TASK_DONE_LISTENER_HPP_

#include <boost/noncopyable.hpp>

#include <string>

namespace rg
{
    /**
     * An abstract base class that defines a type
     * containing the behaviour for a listener interested
     * in knowing when its task is done running.
     *
     * @author Rubens Gomes
     */
    class TaskListener: private boost::noncopyable
    {
    public:
        // dtor
        virtual ~TaskListener() = 0;

        /**
         * The client will get a call back on this
         * method when that task is completed.
         */
        virtual void notifyTaskDone() const = 0;

        /**
         * The client will get a call back on this
         * method when that task is interrupted or stopped
         * while it was being running or in the queue to
         * be run.
         *
         * @param the message associated with the reasons
         * for why the task was interrupted or stopped.
         */
        virtual void notifyTaskFailed(const std::string &) const = 0;

        /**
         * The equal comparison operator.
         *
         * @param the object to compare to.
         * @return true if this and the other object have the
         * same address; false, otherwise.
         */
        bool operator==(const TaskListener &) const;

        /**
         * the not equal comparison operator.
         *
         * @param the object to compare to.
         * @return true if this and the other object have
         * different address; false, otherwise.
         */
        bool operator!=(const TaskListener &) const;

    private:
        // private ctor
        TaskListener();

        // private copy ctor
        TaskListener(const TaskListener &);

        // private copy assignment ctor
        TaskListener & operator=(const TaskListener &);
    };
}

#endif /* THREADPOOL_TASK_DONE_LISTENER_HPP_ */
