/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: event_handler.hpp
 *
 * Date:  Mar 7, 2016
 * ********************************************************
 */
#ifndef REACTOR_EVENT_HANDLER_HPP_
#define REACTOR_EVENT_HANDLER_HPP_

#include <boost/noncopyable.hpp>

#include <map>
#include <string>

namespace rg
{

    /**
     * A HANDLE identifies OS (operating systems)
     * resources, such as, socket network connections,
     * open files, timers, etc.  A HANDLE generates
     * events that are handled by an EventHandler.
     */
    typedef void * HANDLE;

    /**
     * TITLE
     * Types of events handled by the
     * Initiation Dispatcher.
     *
     * DESCRIPTION
     * These values are powers of two so
     * their bits can be efficiently ‘‘or’d’’
     * together to form composite values.
     */
    enum class EventType
    {
        ACCEPT_EVENT = 01,
        READ_EVENT = 02,
        WRITE_EVENT = 04,
        TIMEOUT_EVENT = 010,
        SIGNAL_EVENT = 020,
        CLOSE_EVENT = 040
    };

    std::map<EventType, std::string> EventTypeMap =
    {
            {EventType::ACCEPT_EVENT, "ACCEPT_EVENT"},
            {EventType::READ_EVENT, "READ_EVENT"},
            {EventType::WRITE_EVENT, "WRITE_EVENT"},
            {EventType::SIGNAL_EVENT, "SIGNAL_EVENT"},
            {EventType::CLOSE_EVENT, "CLOSE_EVENT"}
    };

    /**
     * TITLE
     * Abstract base class that serves as the
     * target of the InitiationDispatcher.
     * <p>
     * This class specifies an interface that the Reactor uses to
     * dispatch handleEvent callback method in response to an
     * event generated in the system. Event Handlers should be
     * pre-registered with the Reactor to handle specific events.
     */
    class EventHandler : private boost::noncopyable
    {
    public:
        // dtor
        virtual ~EventHandler() = 0;

        /**
         * Hook method that is called back by the
         * InitiationDispatcher to handle events.
         * <p>
         *
         * @param the event type that is being handled.
         * @param some text message that may be associated
         * with the event.  The message could be empty or
         * null.
         */
        virtual void handleEvent(const EventType &,
                std::string &) = 0;

        /**
         * Hook method that returns the underlying
         * I/O Handle.
         *
         * @return the handle used by the event handler.
         */
        virtual HANDLE getHandle(void) const = 0;

        /**
         * Returns a unique string that identifies this
         * event handler in the system.  This unique
         * id may be used when registering the event handler
         * with the Acceptor InitiationDispatcher.
         *
         * @return unique ID for this event handler
         */
        virtual std::string getId(void) const = 0;
    };
}

#endif /* REACTOR_EVENT_HANDLER_HPP_ */
