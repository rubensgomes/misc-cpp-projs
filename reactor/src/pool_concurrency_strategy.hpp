/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: pool_concurrency_strategy.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_THREADPOOLCONCURRENCYSTRATEGY_HPP_
#define REACTOR_THREADPOOLCONCURRENCYSTRATEGY_HPP_

#include "concurrency_strategy.hpp"

class ThreadPoolConcurrencyStrategy :
        public ConcurrencyStrategy
{
public:
    // ctor
    ThreadPoolConcurrencyStrategy();

    // dtor
    virtual ~ThreadPoolConcurrencyStrategy();

    // Overriden Function
    virtual void activate(const ServiceHandler &) const;
};

#endif /* REACTOR_THREADPOOLCONCURRENCYSTRATEGY_HPP_ */
