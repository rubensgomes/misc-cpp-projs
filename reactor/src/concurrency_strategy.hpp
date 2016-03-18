/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: concurrency_strategy.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_CONCURRENCYSTRATEGY_HPP_
#define REACTOR_CONCURRENCYSTRATEGY_HPP_

#include "service_handler.hpp"

#include <boost/noncopyable.hpp>

namespace rg
{
    /**
     * This interface provides the type of concurrency schemes
     * (thread on demand, thread pool).
     * <p>
     * The Acceptor uses a specific Concurrency Strategy to activate
     * Service Handlers to handle the client-server communication
     * protocol.
     * <p>
     *
     * @author Rubens Gomes
     */
    class ConcurrencyStrategy : private boost::noncopyable
    {
    public:
        // dtor
        virtual ~ConcurrencyStrategy() = 0;

        /**
         * Activates the given service handler by using the respective
         * concurrency scheme.
         *
         * @param the service handler
         */
        virtual void activate(const ServiceHandler &) = 0;
    };
}
#endif /* REACTOR_CONCURRENCYSTRATEGY_HPP_ */
