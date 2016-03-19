/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: creation_strategy.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_CREATIONSTRATEGY_HPP_
#define REACTOR_CREATIONSTRATEGY_HPP_

#include "service_handler.hpp"

#include <boost/noncopyable.hpp>

namespace rg
{
    /**
     * This interface provides the behaviour to be implemented by a
     * strategy object resposinble for creating a service handler.
     *
     * @author Rubens Gomes
     */
    class CreationStrategy : private boost::noncopyable
    {
    public:
        // dtor
        virtual ~CreationStrategy() = 0;

        /**
         * Creates a service handler concrete object using the respective
         * creation strategy.
         *
         * @return the service handler to handle the IO communication
         * protocol with the client.
         * @throws std::exception if it is not possible to
         * instantiate a service handler class.
         */
        virtual ServiceHandler * create(void) = 0;
    };
}

#endif /* REACTOR_CREATIONSTRATEGY_HPP_ */
