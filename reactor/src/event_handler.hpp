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

#include <string>

namespace rg
{

    typedef void * HANDLE;

    enum class EventType
    {
        ACCEPT,
        CLOSE,
        REMOVED,
        SIGNAL
    };

    /**
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
         * Handles the given event type.
         *
         * @param the handle associated with the event.
         * @param the event type that is being handled.
         * @param some text message that may be associated
         * with the event.  The message could be empty or null.
         */
        virtual void handleEvent(const HANDLE &,
                const EventType &,
                const std::string &) = 0;

        /**
         * Returns the handle being used by the event handler.
         *
         * @return the handle used by the event handler.
         */
        virtual HANDLE getHandle(void) const = 0;
    };
}

#endif /* REACTOR_EVENT_HANDLER_HPP_ */
