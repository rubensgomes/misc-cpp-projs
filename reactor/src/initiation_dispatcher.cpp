/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: InitiationDispatcher.cpp
 *
 * Date:  Mar 18, 2016
 * ********************************************************
 */
#include "initiation_dispatcher.hpp"

// threadpool
#include "ondemand_task_thread.hpp"

#include <boost/log/trivial.hpp>

using namespace std;

namespace rg
{

InitiationDispatcher::InitiationDispatcher()
: m_is_closed(false)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher ["
                             << this
                             << "] constructed.";
}

InitiationDispatcher::~InitiationDispatcher()
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher ["
                             << this
                             << "] being destructed.";
}

// synchronized
void InitiationDispatcher::registerHandler(
        const EventHandler & handler,
        const EventType & type)
{
    BOOST_LOG_TRIVIAL(info) <<
            "InitiationDispatcher entering registerHandler.";

    lock_guard<mutex> grd_lock(m_mutex);

    if(m_is_closed)
    {
        throw new runtime_error(
                "The initiation dispatcher is closed.");
    }

    string id = handler.getId();

    BOOST_LOG_TRIVIAL(info) <<
            "Registering event handler w/ID [" +
            id +  "] and type [" +
            EventTypeMap[type] + "]";

    if (m_handlers.find(id))
    {
        throw invalid_argument ("Event handler with ID [" +
                id + "] has already been registered.");
    }

    EventTypeHandler type_handler;
    type_handler.type = type;
    type_handler.handler = handler;

    m_handlers.insert(
            pair<string,EventTypeHandler>(id, type_handler));
}

// synchronized
void InitiationDispatcher::removeHandler(const EventHandler & handler,
        const EventType & type)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher entering removeHandler.";

    lock_guard<mutex> grd_lock(m_mutex);

    string id = handler.getId();

    BOOST_LOG_TRIVIAL(trace) << "Searching event handler w/ID ["
                             << id
                             << "]";

    auto type_handler = m_handlers.find(id);
    if(type_handler != m_handlers.end())
    {
        // found handler
        if (type_handler->second.type == type)
        {
            BOOST_LOG_TRIVIAL(info) << "Removing event handler w/ID ["
                                    << id + "] and type ["
                                    << EventTypeMap[type]
                                    << "]";
            m_handlers.erase(id);
        }
    }
}

// synchronized
void InitiationDispatcher::removeAllHandlers(void)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher entering removeAllHandlers";

    lock_guard<mutex> grd_lock(m_mutex);

    BOOST_LOG_TRIVIAL(info) << "Removing all event handlers";

    m_handlers.clear();
}

// synchronized
void InitiationDispatcher::handleEvents(void)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher entering handleEvents";

    lock_guard<mutex> grd_lock(m_mutex);

    typedef map<string, EventTypeHandler>::iterator hndlr_iter_t;

    string msg = "checking handler ";

    for(hndlr_iter_t iter = m_handlers.begin();
            iter != m_handlers.end();
            iter++)
    {
        msg += iter->second.handler.getId();
        msg += "]";

        BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher "
                                 << msg;

        iter->second.handler.handleEvent(
                EventType::ACCEPT_EVENT, msg);
    }

}

// syncrhonized
void InitiationDispatcher::close(void)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher entering close.";

    lock_guard<mutex> grd_lock(m_mutex);

    closeHandles();
    m_is_closed = true;
}

void InitiationDispatcher::closeHandles(void)
{
    BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher entering closeHandles.";

    typedef map<string, EventTypeHandler>::iterator hndlr_iter_t;

    string msg = "closing event handler w/ID [";

    for(hndlr_iter_t iter = m_handlers.begin();
            iter != m_handlers.end();
            iter++)
    {
        msg += iter->second.handler.getId();
        msg += "]";

        BOOST_LOG_TRIVIAL(trace) << "InitiationDispatcher "
                                 << msg;

        iter->second.handler.handleEvent(
                EventType::CLOSE_EVENT,
                msg);
    }
}

} /* namespace rg */
