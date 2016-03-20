/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: initiation_dispatcher.hpp
 *
 * Date:  Mar 18, 2016
 * ********************************************************
 */
#ifndef REACTOR_INITIATIONDISPATCHER_HPP_
#define REACTOR_INITIATIONDISPATCHER_HPP_

#include "reactor.hpp"

#include <boost/noncopyable.hpp>

#include <map>
#include <string>

namespace rg
{

    /**
     * Singleton class
     * <p>
     * Registers event handlers, and manages events.
     * Once an event is triggered it dispatches to
     * one of the previously registered event handler.
     *
     * @author Rubens Gomes
     */
    class InitiationDispatcher: public Reactor,
        private boost::noncopyable
    {
    public:
        static InitiationDispatcher * instance();

        // Overriden function
        void registerHandler(const EventHandler &,
                const EventType &) override;

        // Overriden function
        void removeHandler(const EventHandler &) override;

        // Overriden function
        void removeAllHandlers(void) override;

        // Overriden function
        void handleEvents(void) override;

        // Overriden function
        void close(void) override;

    private:
        // private ctor
        InitiationDispatcher();

        // private copy ctor
        InitiationDispatcher(const InitiationDispatcher &);

        // private dtor
        virtual ~InitiationDispatcher();

        struct EventTypeHandler
        {
            EventType type;
            EventHandler & handler;
        };

        // closes all handles currently opened
        void closeHandles(void);

        bool m_is_closed;
        std::map<std::string, EventTypeHandler> m_handlers;
    };

} /* namespace rg */

#endif /* REACTOR_INITIATIONDISPATCHER_HPP_ */
