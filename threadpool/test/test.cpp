/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: test.cpp
 *
 * Date:  Jan 14, 2016
 * ********************************************************
 */

#define BOOST_TEST_MODULE ThreadPool Test Suite 

#include "thread_pool_manager.hpp"
#include "thread_ondemand_manager.hpp"
#include "hello_task.hpp"

#include <boost/log/trivial.hpp>
#include <boost/test/included/unit_test.hpp> 

#include <memory>

/**
 * Test Suite for the C++ Thread Pool classes
 *
 * @author Rubens Gomes
 */
BOOST_AUTO_TEST_CASE(threadpool_first_test)
{
    ThreadPoolManager * pool =
            ThreadPoolManager::instance();

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager test creating HelloTask...";

    std::unique_ptr<Task> task (new HelloTask());

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager test pushing task into pool..";

    pool->pushTask(move(task));

    BOOST_LOG_TRIVIAL(trace) << "ThreadPoolManager calling shutdown...";

    pool->shutdown();
}

BOOST_AUTO_TEST_CASE(demandthread_first_test)
{
    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager test creating HelloTask...";

    std::unique_ptr<Task> task(new HelloTask());

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager test creating / launching thread...";

    ThreadOnDemandManager * onDemand =
            ThreadOnDemandManager::instance(std::move(task));

    BOOST_LOG_TRIVIAL(trace) << "ThreadOnDemandManager calling shutdown...";

    onDemand->shutdown();
}
