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

#include "globals.hpp"
#include "task_queue.hpp"
#include "thread_cancellation_point.hpp"
#include "thread_cancellation_exception.hpp"

#include <boost/log/trivial.hpp>
#include <boost/lexical_cast.hpp>

#include <exception>
#include <thread>

using namespace std;

namespace rg
{

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
: m_is_stopped(false),
  m_tasks(),
  m_mutex(),
  m_condition(),
  m_cancel_point()
{
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue ["
                             << this
                             << "] constructed";
}

// synchronized
void TaskQueue::push(unique_ptr<Task> task)
{
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue entering push...";

    lock_guard<mutex> grd_lock(m_mutex);

    if(m_is_stopped)
    {
        throw new std::runtime_error(
           "TaskQueue has been shutdown.  No more tasks are accepted.");
    }

    string id = boost::lexical_cast<string>(this_thread::get_id());
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue "
                             << "thread id ["
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
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue entering pop...";

    unique_lock<mutex> unq_lock(m_mutex);

    string id = boost::lexical_cast<string>(this_thread::get_id());
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue "
                             << "thread id ["
                             << id
                             << "] checking if queue is empty";

    BOOST_LOG_TRIVIAL(trace) << "TaskQueue releasing unique lock...";

    bool is_error = false;

    unq_lock.unlock();
    while(m_tasks.empty())
    {
        m_cancel_point.wait(TaskQueue::s_timeout);
    }

    BOOST_LOG_TRIVIAL(trace) << "TaskQueue "
                             << "thread id ["
                             << id
                             << "] popping task from queue";

    BOOST_LOG_TRIVIAL(trace) << "TaskQueue acquiring unique lock...";
    unq_lock.lock();

    unique_ptr<Task> task = move(m_tasks.front());
    return task;
}

void TaskQueue::shutdown(void)
{
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue entering shutdown...";

    unique_lock<mutex> unq_lock(m_mutex);

    BOOST_LOG_TRIVIAL(trace) << "TaskQueue shutdown started.";
    m_cancel_point.stop();
    m_is_stopped = true;
    BOOST_LOG_TRIVIAL(trace) << "TaskQueue shutdown finished.";
}

}
