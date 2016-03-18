/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_cancellation_exception.hpp
 *
 * Date:  Mar 9, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREADCANCELLATIONEXCEPTION_HPP_
#define THREADPOOL_THREADCANCELLATIONEXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace rg
{
    /**
     * An exception that is raised to be used when
     * stopping a running thread.
     *
     * @author Rubens Gomes
     */
    class ThreadCancellationException : public std::runtime_error
    {
    public:
        // ctor
        ThreadCancellationException(const std::string & what)
            : std::runtime_error(what) {}

        // ctor
        ThreadCancellationException(const char * what)
            : std::runtime_error(what) {}

        // ctor
        ThreadCancellationException()
            : std::runtime_error("") {}

    };
}
#endif /* THREADPOOL_THREADCANCELLATIONEXCEPTION_HPP_ */
