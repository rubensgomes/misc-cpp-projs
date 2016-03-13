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
#include <memory>

#include <boost/test/included/unit_test.hpp> 

#include "thread_pool_manager.hpp"
#include "thread_ondemand_manager.hpp"
#include "hello_task.hpp"

/**
 * Test Suite for the C++ Thread Pool classes
 *
 * @author Rubens Gomes
 */
BOOST_AUTO_TEST_CASE(threadpool_first_test)
{
    ThreadPoolManager * pool =
            ThreadPoolManager::instance();
    std::unique_ptr<Task> task (new HelloTask());
    pool->pushTask(move(task));
    pool->shutdown();
}

BOOST_AUTO_TEST_CASE(demandthread_first_test)
{
    ThreadOnDemandManager * onDemand =
            ThreadOnDemandManager::instance();
    std::unique_ptr<Task> task(new HelloTask());
    onDemand->launchThread(move(task));
    onDemand->shutdown();
}
