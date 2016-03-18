/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: acceptor_strategy_factory.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_ACCEPTORSTRATEGYABSTRACTFACTORY_HPP_
#define REACTOR_ACCEPTORSTRATEGYABSTRACTFACTORY_HPP_

#include "creation_strategy.hpp"
#include "concurrency_strategy.hpp"

#include <boost/noncopyable.hpp>

namespace rg
{
    /**
     * An Abstract Factory interface used for creating Acceptor
     * Strategy objects.
     *
     * @author Rubens Gomes
     */
    class AcceptorStrategyAbstractFactory :
            private boost::noncopyable
    {
    public:
        // dtor
        virtual ~AcceptorStrategyAbstractFactory() = 0;

        /**
         * Creates a new CreationStrategy object.
         *
         * @return the creation strategy used by the Acceptor
         * when creating a new Service Handler.
         */
        virtual CreationStrategy * createCreationStrategy(void) = 0;

        /**
         * Creates a new ConcurrencyStrategy object.
         *
         * @return the concurrency strategy used by the Acceptor
         * when activating a Service Handler to handle the client-
         * server communication protocol.
         */
        virtual ConcurrencyStrategy * createConcurrencyStrategy(void) = 0;
    };
}
#endif /* REACTOR_ACCEPTORSTRATEGYABSTRACTFACTORY_HPP_ */
