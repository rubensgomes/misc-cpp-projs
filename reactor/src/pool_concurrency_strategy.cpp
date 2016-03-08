/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: pool_concurrency_strategy.cpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#include <boost/log/trivial.hpp>

#include <stddef.h>

// threadpool
#include <thread_pool_manager.hpp>
#include <task.hpp>

#include "pool_concurrency_strategy.hpp"

ThreadPoolConcurrencyStrategy::ThreadPoolConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolConcurrencyStrategy ["
                             << this
                             << "] being constructed.";
}

ThreadPoolConcurrencyStrategy::~ThreadPoolConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolConcurrencyStrategy ["
                             << this
                             << "] being destructed.";
}

void ThreadPoolConcurrencyStrategy::activate(
        const ServiceHandler & handler) const
{
    ThreadPoolManager * poolMgr =
            ThreadPoolManager::instance();

    Task * task = handler.getTask();

    if(task == NULL)
    {
        BOOST_LOG_TRIVIAL(info) << "No task to be launched.";
    }
    else
    {
        BOOST_LOG_TRIVIAL(trace) << "PoolMgr pushing task id ["
                                 << task->getId()
                                 << "]";
        poolMgr->pushTask(task);
    }
}
