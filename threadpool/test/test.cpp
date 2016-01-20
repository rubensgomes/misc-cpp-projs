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

/**
 * Test Suite for the C++ Thread classes
 *
 * @author Rubens Gomes
 */
BOOST_AUTO_TEST_CASE(threadpool_first_test)
{
    ThreadPool * pool = ThreadPool::instance();
    int nr_threads = pool->getTotalThreads();
    BOOST_TEST(nr_threads);
    BOOST_TEST(nr_threads == THREAD_POOL_SIZE);

    pool->shutdown();
}
