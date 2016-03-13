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
#include <exception>

#include <boost/log/trivial.hpp>

#include "globals.hpp"
#include "task.hpp"
#include "thread_cancellation_exception.hpp"

using namespace std;

// static variables
double Task::s_counter = 0;
bool Task::s_is_stopped = false;

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
    try
    {
        BOOST_LOG_TRIVIAL(trace) << "running task.";
        do_run(); // private pure virtual
        BOOST_LOG_TRIVIAL(trace) << "Notifying listeners.";
        notifyListeners();
    }
    catch(const ThreadCancellationException & ex)
    {
        // TODO
    }
    catch(const std::exception & ex)
    {
        // TODO
    }
    catch(...)
    {
        // TODO
    }

}

void Task::stopAll(void)
{
    Task::s_is_stopped = true;
}

void Task::addListener(unique_ptr<TaskListener> listener)
{
    m_listeners.push_back(move(listener));
}

void Task::removeListener(const unique_ptr<TaskListener> & listener)
{
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
    return m_id;
}
