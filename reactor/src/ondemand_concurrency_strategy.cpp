/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: ondemand_concurrency_strategy.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include <stddef.h>

// threadpool
#include <thread_ondemand_manager.hpp>
#include <task.hpp>

#include "ondemand_concurrency_strategy.hpp"

ThreadOnDemandConcurrencyStrategy::ThreadOnDemandConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy ["
                             << this
                             << "] being constructed.";
}

ThreadOnDemandConcurrencyStrategy::~ThreadOnDemandConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy ["
                             << this
                             << "] being destructed.";
}

void ThreadOnDemandConcurrencyStrategy::activate(
        const ServiceHandler & handler) const
{
    ThreadOnDemandManager * onDemandMgr =
            ThreadOnDemandManager::instance();

    Task * task = handler.getTask();

    if(task == NULL)
    {
        BOOST_LOG_TRIVIAL(info) << "No task to be launched.";
    }
    else
    {
        BOOST_LOG_TRIVIAL(trace) << "OnDemand launching task id ["
                                 << task->getId()
                                 << "]";
        onDemandMgr->launchThread(task);
    }

}
