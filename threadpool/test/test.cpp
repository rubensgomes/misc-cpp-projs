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
#include <boost/test/included/unit_test.hpp> 

#include "thread_pool.hpp"
#include "hello_task.hpp"
#include "demand_task_thread.hpp"

/**
 * Test Suite for the C++ Thread Pool classes
 *
 * @author Rubens Gomes
 */
BOOST_AUTO_TEST_CASE(threadpool_first_test)
{
    ThreadPool * pool = ThreadPool::instance();
    pool->shutdown();
}

BOOST_AUTO_TEST_CASE(demandthread_first_test)
{
    HelloTask task;
    OnDemandTaskThread thread(task);
    thread.stopMe();
}
