/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: demand_task_thread.hpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_DEMAND_TASK_THREAD_HPP_
#define THREADPOOL_DEMAND_TASK_THREAD_HPP_

#include <boost/thread.hpp>

#include "i_task.hpp"

// TODO: move to a properties file
// time to wait for thread to stop
const int STOP_WAIT_TIME = 3000; // msecs

/**
 * This class creates and launches a thread to
 * execute the given task using the "On Demand
 * Thread Strategy".
 *
 * @author Rubens Gomes
 */
class OnDemandTaskThread
{
public:
    /**
     * Constructor
     *
     * @param task that to be executed by the thread.
     */
    OnDemandTaskThread(const ITask &);

    /**
     * Copy constructor.  The copy constructor is required
     * because the newly created thread will need to make
     * a copy of this object.
     *
     * @param the task thread to be copied.
     */
    OnDemandTaskThread(const OnDemandTaskThread &);

    /**
     * Destructor.
     */
    virtual ~OnDemandTaskThread();

    /**
     * A callable that contains the code to be
     * executed by the thread.  Internally it
     * delegates to the ITask run() method, and it
     * notifies any task listener when task is done.
     */
    void operator()(void);

    /**
     * Nicely stops the running thread.
     */
    void stopMe(void);

private:
    // following operators are not used in this class
    bool operator==(const OnDemandTaskThread &) const;
    bool operator!=(const OnDemandTaskThread &) const;

    const ITask & m_task;
    bool m_is_stopped;
    boost::mutex m_mutex;
};

#endif /* THREADPOOL_DEMAND_TASK_THREAD_HPP_ */
