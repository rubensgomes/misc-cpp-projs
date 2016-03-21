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

#include "event_handler.hpp"
#include "reactor.hpp"

#include <boost/noncopyable.hpp>

#include <map>
#include <mutex>
#include <string>

namespace rg
{

    /**
     * Singleton class
     * <p>
     * Demultiplex and dispatch EventHandlers
     * in response to client requests.
     *
     * @author Rubens Gomes
     */
    class InitiationDispatcher: public Reactor,
        private boost::noncopyable
    {
    public:
        // Singleton instance function
        static InitiationDispatcher * instance();

        // Overriden function
        /**
         * Register an Acceptor EventHandler of a
         * particular EventType (e.g., READ_EVENT,
         * ACCEPT_EVENT, etc.).
         *
         * @param the Acceptor EventHandler
         * @param the EventType
         */
        void registerHandler(const EventHandler &,
                const EventType &) override;

        // Overriden function
        /**
         * Remove an EventHandler of a particular
         * EventType.
         *
         * @param
         */
        void removeHandler(const EventHandler &,
                const EventType &) override;

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
        std::mutex m_mutex;
    };

} /* namespace rg */

#endif /* REACTOR_INITIATIONDISPATCHER_HPP_ */
