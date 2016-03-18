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

// threadpool
#include "thread_pool_manager.hpp"
#include "task.hpp"

#include "pool_concurrency_strategy.hpp"

#include <boost/log/trivial.hpp>

using namespace std;

namespace rg
{

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
    unique_ptr<Task> task = handler.getTask();

    ThreadPoolManager * poolMgr =
            ThreadPoolManager::instance();

    BOOST_LOG_TRIVIAL(trace) << "PoolMgr pushing task id ["
                             << task->getId()
                             << "]";
    poolMgr->pushTask(move(task));
}

}
