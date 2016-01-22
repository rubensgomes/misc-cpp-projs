/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: hello_task.hpp
 *
 * Date:  Jan 21, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_TEST_HELLO_TASK_HPP_
#define THREADPOOL_TEST_HELLO_TASK_HPP_

#include "i_task.hpp"

/**
 * A simple Hello World task used for testing
 * the thread code.
 *
 * @author Rubens Gomes
 */
class HelloTask: public ITask
{
public:
    HelloTask();
    virtual ~HelloTask();

    // base class function
    ITask * clone(void) const;

    // base class function
    void do_run(void) const;
};

#endif /* THREADPOOL_TEST_HELLO_TASK_HPP_ */
