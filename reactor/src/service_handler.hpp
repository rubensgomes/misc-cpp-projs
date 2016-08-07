/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: service_handler.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_SERVICEHANDLER_HPP_
#define REACTOR_SERVICEHANDLER_HPP_

#include "event_handler.hpp"

#include "task.hpp" // threadpool

#include <memory>

namespace rg
{
    /**
     * This abstract class provides a generic interface for
     * processing services. Applications must customize this
     * class to perform a particular type of service.
     *
     * @author Rubens Gomes
     */
    class ServiceHandler: public EventHandler
    {
    public:
        // dtor
        virtual ~ServiceHandler() = 0;

        /**
         * The open method initializes the Service Handler with the
         * IO Socket Handle used for the client-server communication
         * protocol.
         * <p>
         * It is called by an Acceptor after a connection is
         * established.  This must be done upfront before any
         * other methods are called on the service handler.
         *
         */
        virtual void open() = 0;

        /**
         * Closes this service handler by properly closing
         * and releasing any IO handle connections.
         */
        virtual void close(void) = 0;

        /**
         * Implements the protocol (conversation) between client
         * and server.
         */
        virtual void run(void) = 0;

        /**
         * Gets the task.
         *
         * @return the task to be executed when handling the service.
         */
        virtual std::unique_ptr<Task> getTask(void) const = 0;
    };
}
#endif /* REACTOR_SERVICEHANDLER_HPP_ */
