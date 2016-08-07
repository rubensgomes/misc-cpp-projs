/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: TestAcceptor.cpp
 *
 * Date:  Mar 20, 2016
 * ********************************************************
 */
#include "service_handler.hpp"
#include "test_acceptor.hpp"

#include <boost/log/trivial.hpp>

#include <exception>

using namespace boost::asio::ip;
using namespace std;

namespace rg
{

TestAcceptor::TestAcceptor(const boost::asio::io_service & io_service)
:m_is_initialized(false),
 m_ioservice(io_service),
 m_socket(io_service),
 m_factory()
{
    BOOST_LOG_TRIVIAL(trace) << "TestAcceptor ["
                             << this
                             << "] constructed.";
}

TestAcceptor::~TestAcceptor()
{
    BOOST_LOG_TRIVIAL(trace) << "TestAcceptor ["
                             << this
                             << "] being destructed.";
}

void TestAcceptor::open(int port_nr,
        Reactor & reactor,
        const AcceptorStrategyAbstractFactory & factory)
{
    BOOST_LOG_TRIVIAL(trace) << "TestAcceptor entering open...";

    if(m_is_initialized)
    {
        throw runtime_error("Acceptor has already been initialized.");
    }

    tcp::endpoint endpoint(tcp::v4(), port_nr);
    m_boost_acceptor(m_ioservice, endpoint);

    // Register acceptor with the Reactor Initiation
    // Dispatcher, which "double dispatches"
    // the TestAcceptor::get_handle() method
    // to obtain the HANDLE.
    const EventHandler & my_self = *this;

    reactor.registerHandler(my_self, EventType::ACCEPT_EVENT);
    m_factory = factory;
    m_is_initialized = true;
}

void TestAcceptor::handleEvent(const EventType & type,
                const std::string & msg)
{
    BOOST_LOG_TRIVIAL(trace) << "TestAcceptor entering handleEvent...";

    BOOST_LOG_TRIVIAL(debug) << "Event type [" + EventTypeMap[type] + "]";

    if(type == EventType::ACCEPT_EVENT)
    {
        m_boost_acceptor.accept(m_socket);
        ServiceHandler * handler =
                m_factory.createCreationStrategy()->create();
        m_factory.createConcurrencyStrategy()->activate(*handler);
    }
}

} /* namespace rg */
