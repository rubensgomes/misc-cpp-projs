/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: ondemand_concurrency_strategy.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_THREADONDEMANDCONCURRENCYSTRATEGY_HPP_
#define REACTOR_THREADONDEMANDCONCURRENCYSTRATEGY_HPP_

#include "concurrency_strategy.hpp"

/**
 * The thread on demand concurrency strategy spawns a new
 * thread to activate and run a service handler.
 *
 * @author Rubens Gomes
 */
class ThreadOnDemandConcurrencyStrategy :
        public ConcurrencyStrategy
{
public:
    // ctor
    ThreadOnDemandConcurrencyStrategy();

    // dtor
    virtual ~ThreadOnDemandConcurrencyStrategy();

    // Overriden function
    virtual void activate(const ServiceHandler &) const;

};

#endif /* REACTOR_THREADONDEMANDCONCURRENCYSTRATEGY_HPP_ */
