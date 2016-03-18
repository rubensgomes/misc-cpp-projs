/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TASK_HPP_
#define THREADPOOL_TASK_HPP_

#include "task_listener.hpp"
#include "thread_cancellation_point.hpp"

#include <boost/noncopyable.hpp>

#include <memory>
#include <mutex>
#include <vector>

namespace rg
{
    /**
     * An abstract base class that defines a
     * type for a task to be executed from a
     * separate thread.
     *
     * This class is NOT thread-safe.  Since a
     * task should be executed within a single
     * separate thread, the author did not concern
     * about making this class thread-safe.
     *
     * @author Rubens Gomes
     */
    class Task : private boost::noncopyable
    {
    public:
        /**
         * Stops all tasks.  It sets a flag in attempt to
         * break out this thread execution.
         */
        static void stopAll(void);

        /**
         * @return the status of the class static stop flag.
         */
        static bool isStopped(void);

        // ctor
        Task();

        // move ctor
        Task(Task &&);

        // dtor
        virtual ~Task();

        /**
         * The run method should contain the code that is
         * to be executed from a thread.  In order for this
         * task to be interrupted the user should provide
         * an interrupt thread point by calling thread wait(),
         * for example.
         */
        void run(void) const;

        /**
         * Registers an observer which wants be notified
         * when this task is done.
         *
         * @param a listener that is to be registered with
         * this task.  The ownership of the listener is moved
         * to the task instance.
         */
        void addListener(std::unique_ptr<TaskListener>);

        /**
         * Removes a previously registered observer of
         * this task.
         *
         * @param a listener that is to be un-registered.
         */
        void removeListener(const std::unique_ptr<TaskListener> &);

        /**
         * Every task is uniquely identified by
         * a unique id.
         *
         * @return my id.
         */
        double getId(void) const;

    private:
        // private copy ctor
        Task(const Task &);

        // private copy assignment ctor
        Task & operator=(const Task &);

        // following operators are not used in this class
        bool operator==(const Task &) const;
        bool operator!=(const Task &) const;

        /**
         * This method should implement whatever the task
         * needs to accomplish when it is executed by a
         * separate thread.
         */
        virtual void do_run(void) const = 0;

        /**
         * The intent of this method is to notify
         * registered listeners when this task run
         * is completed.  This function is automatically
         * called when do_run() returns.
         */
        void notifyListeners(void) const;

        double m_id;
        std::vector<std::unique_ptr<TaskListener>> m_listeners;
        ThreadCancellationPoint m_cancel_point;

        // static variables
        static std::mutex s_mutex;
        static double s_counter;
        static bool s_is_stopped;
    };
}
#endif /* THREADPOOL_TASK_HPP_ */
