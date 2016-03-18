/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: constants.hpp
 *
 * Date:  Mar 5, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_CONSTANTS_HPP_
#define THREADPOOL_CONSTANTS_HPP_

#include <chrono>


namespace rg
{
    typedef std::chrono::duration<int,std::milli> millisecs_t;

    // TODO: move to a properties file

    // time to wait for threads in pool to shutdown
    constexpr int SHUTDOWN_WAIT_TIME = 3000; // msecs

    // time to wait for thread to stop
    constexpr int STOP_WAIT_TIME = 3000; // msecs

    // default number of threads created in the thread pool
    constexpr int THREAD_POOL_SIZE = 2;

    // time to sleep running thread to provide
    // an interrupt point
    constexpr int SLEEP_WAIT_TIME = 1000; // msecs
}

#endif /* THREADPOOL_CONSTANTS_HPP_ */
