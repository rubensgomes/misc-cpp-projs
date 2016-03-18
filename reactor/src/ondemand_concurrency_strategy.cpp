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
#include "ondemand_concurrency_strategy.hpp"

// threadpool
#include "thread_ondemand_manager.hpp"
#include "task.hpp"

#include <boost/log/trivial.hpp>

using namespace std;

namespace rg
{

ThreadOnDemandConcurrencyStrategy::ThreadOnDemandConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy ["
                             << this
                             << "] constructed.";
}

ThreadOnDemandConcurrencyStrategy::~ThreadOnDemandConcurrencyStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy ["
                             << this
                             << "] being destructed.";
}

void ThreadOnDemandConcurrencyStrategy::activate(
        const ServiceHandler & handler)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy entering activate ...";

    unique_ptr<Task> task = handler.getTask();

    ThreadOnDemandManager::instance(move(task));

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandConcurrencyStrategy activated";
}

}
