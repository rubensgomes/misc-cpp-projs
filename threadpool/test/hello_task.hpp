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

#include "task.hpp"

namespace rg
{

    /**
     * A simple Hello World task used for testing
     * the thread code.
     *
     * @author Rubens Gomes
     */
    class HelloTask: public Task
    {
    public:
        // c-tor
        HelloTask();

        // d-tor
        virtual ~HelloTask();

        // base class function
        void do_run(void) const override;
    };

}
#endif /* THREADPOOL_TEST_HELLO_TASK_HPP_ */
