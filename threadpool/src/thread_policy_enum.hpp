/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: thread_policy_enum.hpp
 *
 * Date:  Mar 3, 2016
 * ********************************************************
 */
#ifndef THREADPOOL_THREAD_POLICY_ENUM_HPP_
#define THREADPOOL_THREAD_POLICY_ENUM_HPP_

namespace rg
{
    enum class ThreadPolicy
    {
        THREAD_ONDEMAND,
        THREAD_POOL
    };
}
#endif /* THREADPOOL_THREAD_POLICY_ENUM_HPP_ */
