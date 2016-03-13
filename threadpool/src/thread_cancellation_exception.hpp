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

#include <exception>
#include <string>

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
    explicit ThreadCancellationException(const std::string & what)
        : std::runtime_error(what) {}

    // ctor
    ThreadCancellationException(const char * what)
        : std::runtime_error(what) {}
};

#endif /* THREADPOOL_THREADCANCELLATIONEXCEPTION_HPP_ */
