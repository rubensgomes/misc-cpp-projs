/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: task.cpp
 *
 * Date:  Jan 16, 2016
 * ********************************************************
 */

#include "globals.hpp"
#include "task.hpp"
#include "thread_cancellation_exception.hpp"

#include <boost/log/trivial.hpp>

#include <exception>

using namespace std;

namespace rg
{


// static variables
mutex Task::s_mutex;
double Task::s_counter = 0;
bool Task::s_is_stopped = false;


// synchronized static function
void Task::stopAll(void)
{
    lock_guard<mutex> grd_lock(Task::s_mutex);
    Task::s_is_stopped = true;
}

// synchronized static function
bool Task::isStopped(void)
{
    lock_guard<mutex> grd_lock(Task::s_mutex);
    return Task::s_is_stopped;
}

// ctor
Task::Task()
: m_id(++Task::s_counter),
  m_listeners(),
  m_cancel_point()
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] with id ["
                             << m_id
                             << "] constructed.";
}

// move ctor
Task::Task(Task && rhs)
: m_id(rhs.m_id),
  m_listeners(move(rhs.m_listeners)),
  m_cancel_point(rhs.m_cancel_point)
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] with id ["
                             << m_id
                             << "] move constructed.";
}

// dtor
Task::~Task()
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             <<  this
                             << "] with id ["
                             << m_id
                             << "] being destructed.";
}

void Task::run(void) const
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             << this
                             << "] entering run...";

    try
    {
        BOOST_LOG_TRIVIAL(trace) << "Task ["
                                 <<  this
                                 << "] running task with id ["
                                 << m_id
                                 << "].";
        do_run(); // private pure virtual
        BOOST_LOG_TRIVIAL(trace) << "Task Notifying listeners.";
        notifyListeners();
    }
    catch(const ThreadCancellationException & ex)
    {
        BOOST_LOG_TRIVIAL(error) << "Task exception ["
                                 << ex.what()
                                 << "].";
    }
    catch(const std::exception & ex)
    {
        BOOST_LOG_TRIVIAL(error) << "Task exception ["
                                 << ex.what()
                                 << "].";
    }
    catch(...)
    {
        BOOST_LOG_TRIVIAL(error) << "Task some other error occurred.";
    }
}

void Task::addListener(unique_ptr<TaskListener> listener)
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             << this
                             << "] adding listener.";

    m_listeners.push_back(move(listener));
}

void Task::removeListener(const unique_ptr<TaskListener> & listener)
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             << this
                             << "] removing listener.";

    typedef vector<unique_ptr<TaskListener>>::iterator iter_t;

    for(iter_t it=m_listeners.begin();
            it!=m_listeners.end();
            it++)
    {
        if( *it == listener )
        {
            m_listeners.erase(it);
        }
    }
}

void Task::notifyListeners(void) const
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             << this
                             << "] entering notifyListeners...";

    if(m_listeners.empty())
    {
        BOOST_LOG_TRIVIAL(trace) << "Task no listeners to notify.";
        return;
    }

    BOOST_LOG_TRIVIAL(trace) << "Task notifying listener.";

    for(auto & listener : m_listeners)
    {
        if(listener != nullptr)
        {
            BOOST_LOG_TRIVIAL(trace) << "notifying listener...";
            listener->notifyTaskDone();
        }
    }
}

double Task::getId(void) const
{
    BOOST_LOG_TRIVIAL(trace) << "Task ["
                             << this
                             << "] entering getId...";
    return m_id;
}

}
