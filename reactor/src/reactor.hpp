/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: reactor.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_REACTOR_HPP_
#define REACTOR_REACTOR_HPP_

#include <boost/noncopyable.hpp>

#include "event_handler.hpp"

/**
 * Reactor provides a high level interface to listen and react to
 * events generated in the system.  Once the Reactor detects an
 * event, it dispatches that event to one of the registered event
 * handlers.
 * <p>
 * For example, a Reactor may be implemented by a "Dispatcher"
 * passive network reactive object.  A network dispatcher object
 * binds and listens on a given IP/Port address, and "waits" for an
 * incoming connection request (event) to arrive.  Once a connection
 * request (event) arrives, the network dispatcher reacts to that
 * connection request by handling it to the appropriate "Event
 * Handler".
 * <p>
 * Reactor is a design pattern commonly used to implement reactive
 * networking communication services.  Further information about
 * this design pattern can be found at:
 * <p>
 * <pre>
 * D. C. Schmidt,  Reactor:  An Object Behavioral Pattern for
 * Concurrent  Event  Demultiplexing  and  Event  Handler
 * Dispatching,  in Pattern  Languages  of  Program  Design
 * (J.  O. Coplien and D. C. Schmidt, eds.),
 * pp. 52eading, MA: Addison-Wesley, 1995.
 * </pre>
 * <p>
 *
 * @author Rubens Gomes
 */
class Reactor : private boost::noncopyable
{
public:
    // dtor
    virtual ~Reactor() = 0;

    /**
     * Registers an event handler (e.g., Acceptor) which is
     * interested in receiving and processing that event. At most
     * one handler for a given handle ID can be registered.
     * Duplicate handle IDs are not permitted.
     *
     * @param the event handler that will handle the event.
     * @param the event type that the event handler is
     * interested in.
     */
    virtual void registerHandler(const EventHandler &,
            const EventType &) = 0;

    /**
     * De-registers the given event handler.
     *
     * @param the event handler previously registered.
     */
    virtual void removeHandler(const EventHandler &) = 0;

    /**
     * De-registers all event handlers.
     */
    virtual void removeAllHandlers(void) = 0;

    /**
     * Initiates the handling of events.
     */
    virtual void handleEvents(void) = 0;

    /**
     * Close all resources used by the Reactor,  and stops handling
     * further events.  Basically it shuts down the Reactor.
     */
    virtual void close(void) = 0;

};

#endif /* REACTOR_REACTOR_HPP_ */