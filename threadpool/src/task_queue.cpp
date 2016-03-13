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
#include <thread>

#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

#include "globals.hpp"
#include "task_queue.hpp"
#include "thread_cancellation_point.hpp"

using namespace std;

// static singleton instance
TaskQueue * TaskQueue::s_instance = nullptr;

millisecs_t TaskQueue::s_timeout;

// static singleton instance method
TaskQueue * TaskQueue::instance()
{
    if(TaskQueue::s_instance == nullptr)
    {
        TaskQueue::s_instance = new TaskQueue();
        TaskQueue::s_timeout = millisecs_t(SLEEP_WAIT_TIME);
    }

    return TaskQueue::s_instance;
}

// private ctor
TaskQueue::TaskQueue()
: m_tasks(),
  m_mutex(),
  m_condition(),
  m_cancel_point()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue ["
                             << this
                             << "] singleton constructed";
}

// synchronized
void TaskQueue::push(unique_ptr<Task> task)
{
    lock_guard<mutex> lock(m_mutex);

    string id = boost::lexical_cast<string>(this_thread::get_id());
    BOOST_LOG_TRIVIAL(trace) << "thread id ["
                             << id
                             << "] pushing task to queue";

    m_tasks.push(move(task));

    // only at most *ONE* single thread can execute a
    // given task at a time.  We therefore only need
    // to nofiy *ONE* of the threads waiting.
    m_condition.notify_one();
}

// synchronized method
unique_ptr<Task> TaskQueue::pop(void)
{
    lock_guard<mutex> lock(m_mutex);

    string id = boost::lexical_cast<string>(this_thread::get_id());
    BOOST_LOG_TRIVIAL(trace) << "thread id ["
                             << id
                             << "] checking if queue is empty";

    while(m_tasks.empty())
    {
        m_cancel_point.wait(TaskQueue::s_timeout);
    }

    BOOST_LOG_TRIVIAL(trace) << "thread id ["
                             << id
                             << "] popping task from queue";

    unique_ptr<Task> task = move(m_tasks.front());
    return task;
}

void TaskQueue::shutdown(void)
{
    m_cancel_point.stop();
}
