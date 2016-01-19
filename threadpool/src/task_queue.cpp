/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task_queue.cpp
 *
 * Date:  Jan 19, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include <stddef.h>

#include "task_queue.hpp"

// *static* singleton instance
TaskQueue * TaskQueue::s_instance = NULL;

// *static* singleton instance method
TaskQueue * TaskQueue::instance()
{
    if(TaskQueue::s_instance == NULL)
    {
        TaskQueue::s_instance = new TaskQueue();
    }

    return TaskQueue::s_instance;
}

// private ctor
TaskQueue::TaskQueue()
{
}

// private dtor
TaskQueue::~TaskQueue()
{
}

// synchronized method
void TaskQueue::push(ITask * task)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "pushing task to queue";
    m_tasks.push_back(task);
    m_condition.notify_all();
}

// synchronized method
ITask & TaskQueue::pop(void)
{
    boost::unique_lock<boost::mutex> lock(m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "checking if queue is empty";
    while(m_tasks.empty())
    {
        // Notice that the lock is passed to wait: wait
        // will atomically add the thread to the set of
        // threads waiting on the condition variable,
        // and unlock the m_mutex. When the thread is woken,
        // the m_mutex will be locked again before the call
        // to wait returns. This allows other threads to
        // acquire the m_mutex in order to update the
        // shared data, and ensures that the data associated
        // with the condition is correctly synchronized.
        m_condition.wait(lock);
    }

    BOOST_LOG_TRIVIAL(trace) << "popping task from queue";
    ITask & task = m_tasks.front();
    return task;
}

