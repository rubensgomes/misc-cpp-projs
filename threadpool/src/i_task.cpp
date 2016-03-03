/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: i_task.cpp
 *
 * Date:  Jan 16, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>
#include <algorithm>

#include "i_task.hpp"

// *static* object
double ITask::s_counter = 0;

// ctor
ITask::ITask()
{
    m_id = ++ITask::s_counter;

    BOOST_LOG_TRIVIAL(trace) << "ITask ["
                             <<  this
                             << "] with id ["
                             << m_id
                             << "] constructed.";
}

// dtor
ITask::~ITask()
{
    BOOST_LOG_TRIVIAL(trace) << "ITask ["
                             <<  this
                             << "] with id ["
                             << m_id
                             << "] destructed.";

}

void ITask::run(void) const
{
    do_run(); // private pure virtual
    BOOST_LOG_TRIVIAL(trace) << "Notifying listeners.";
    notifyListeners();
}

void ITask::addListener(ITaskListener * listener)
{
    m_listeners.push_back(listener);
}

void ITask::removeListener(ITaskListener & listener)
{
    typedef boost::ptr_vector<ITaskListener>::iterator iter;
    for(iter it=m_listeners.begin(); it!=m_listeners.begin();
            it++)
    {
        if( *it == listener )
        {
            m_listeners.release(it);
        }
    }
}

void ITask::notifyListeners(void) const
{
    for(auto & listener : m_listeners)
    {
        BOOST_LOG_TRIVIAL(trace) << "notifying listener...";
        listener.notifyTaskDone();
    }
}

double ITask::getId(void) const
{
    return m_id;
}
