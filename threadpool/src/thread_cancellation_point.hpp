/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_cancellation_point.hpp
 *
 * Date:  Mar 9, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREADCANCELLATIONPOINT_HPP_
#define THREADPOOL_THREADCANCELLATIONPOINT_HPP_

#include "globals.hpp"

#include <condition_variable>
#include <mutex>

namespace rg
{
    /**
     * This class is used to interrupt and stop running
     * threads.
     *
     * @author Rubens Gomes
     */
    class ThreadCancellationPoint
    {
    public:
        // ctor
        ThreadCancellationPoint();

        // copy ctor
        ThreadCancellationPoint(const ThreadCancellationPoint &);

        // dtor
        virtual ~ThreadCancellationPoint();

        /**
         * Uses a thread condition variable to cause
         * the running thread to wait for some time.
         *
         * @param the timeout to wait.
         * @throws ThreadCancellationException if stop has been
         * called, or if the time is std::cv_status::no_timeout
         */
        void wait(const millisecs_t &);

        /**
         * Changes the stop flag to true to allow any threads
         * in wait state to raise an exception.  The exception
         * allows handlers to properly clean up any resources
         * prior to stopping the running thread.
         */
        void stop(void);

    private:
        // private copy assignment
        ThreadCancellationPoint& operator=(const ThreadCancellationPoint &);

        // following operators are not used in this class
        bool operator==(const ThreadCancellationPoint &) const;
        bool operator!=(const ThreadCancellationPoint &) const;

        bool m_is_stopped;
        std::mutex m_mutex;
        std::condition_variable m_condition;
    };
}
#endif /* THREADPOOL_THREADCANCELLATIONPOINT_HPP_ */
