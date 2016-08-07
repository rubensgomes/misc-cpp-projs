/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: acceptor.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_ACCEPTOR_HPP_
#define REACTOR_ACCEPTOR_HPP_

#include "acceptor_strategy_factory.hpp"
#include "event_handler.hpp"
#include "reactor.hpp"

namespace rg
{
    /**
     * The Acceptor type used for initializing network services.
     * <p>
     * The purpose of the Acceptor class is to decouple the passive
     * initialization of a service from the tasks performed once a
     * service is initialized.  For instance, the acceptor object
     * handles a connection dispatched from the Reactor object.
     * While handling the connection event the Acceptor creates the
     * Service Handler using a creation strategy (on demand,
     * singleton, thread pool) and delegates to that Service Handler
     * to implement the client-server communication protocol.
     *
     * @author Rubens Gomes
     */
    class Acceptor: public EventHandler
    {
    public:
        // dtor
        virtual ~Acceptor() = 0;

        /**
         * Initializes the acceptor by creating and binding to
         * to a server socket using the given port number,
         * and then registering itself with the given reactor.
         *
         * @param port_nr the port_nr the IO Handle will bind to.
         * @param the reactor the Reactor that handles events
         * and dispatches to pre-registered Acceptor Event Handlers.
         * @param the factory that uses different strategies to
         * create and activate service handlers.
         */
        virtual void open(int port_nr,
                Reactor &,
                const AcceptorStrategyAbstractFactory &) = 0;
    };
}
#endif /* REACTOR_ACCEPTOR_HPP_ */
