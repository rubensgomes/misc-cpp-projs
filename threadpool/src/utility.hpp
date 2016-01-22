/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: utility.hpp
 *
 * Date:  Jan 20, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_UTILITY_HPP_
#define THREADPOOL_UTILITY_HPP_

#include <boost/noncopyable.hpp>

/**
 * A Utility class used by the thread classes.
 *
 * @author Rubens Gomes
 */
class Utility : private boost::noncopyable
{
public:
    /**
     * @return the current running thread id.
     */
    static std::string getRunningThreadId(void);

private:
    Utility();
    ~Utility();
};

#endif /* THREADPOOL_UTILITY_HPP_ */
