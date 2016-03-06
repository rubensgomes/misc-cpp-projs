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
#include <boost/log/trivial.hpp>

#include "task.hpp"

// *static* object
double Task::s_counter = 0;

// ctor
Task::Task()
{
    m_id = ++Task::s_counter;

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
                             << "] destructed.";

}

void Task::run(void) const
{
    do_run(); // private pure virtual
    BOOST_LOG_TRIVIAL(trace) << "Notifying listeners.";
    notifyListeners();
}

void Task::addListener(TaskListener * listener)
{
    m_listeners.push_back(listener);
}

void Task::removeListener(TaskListener & listener)
{
    typedef boost::ptr_vector<TaskListener>::iterator iter;
    for(iter it=m_listeners.begin(); it!=m_listeners.begin();
            it++)
    {
        if( *it == listener )
        {
            m_listeners.release(it);
        }
    }
}

void Task::notifyListeners(void) const
{
    for(auto & listener : m_listeners)
    {
        BOOST_LOG_TRIVIAL(trace) << "notifying listener...";
        listener.notifyTaskDone();
    }
}

double Task::getId(void) const
{
    return m_id;
}
