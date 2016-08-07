/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: test_acceptor.hpp
 *
 * Date:  Mar 20, 2016
 * ********************************************************
 */
#ifndef REACTOR_TESTACCEPTOR_HPP_
#define REACTOR_TESTACCEPTOR_HPP_

#include "acceptor.hpp"
#include "acceptor_strategy_factory.hpp"
#include "reactor.hpp"

#include <boost/asio.hpp>

#include <string>

namespace rg
{

    /**
     * Concrete Acceptor Event Handler.
     *
     * @author Rubens Gomes
     */
    class TestAcceptor: public Acceptor
    {
    public:
        // ctor
        /**
         * The concrete class constructor.
         *
         * @param the io_service represents your
         * program's link to the operating system's
         * I/O services.
         */
        TestAcceptor(const boost::asio::io_service &);

        // dtor
        virtual ~TestAcceptor();

        // Overriden function
        void open(int port_nr,
                Reactor &,
                const AcceptorStrategyAbstractFactory &) override;

        // Overriden function
        void handleEvent(const EventType &,
                const std::string &) override;

        // Overriden function
        HANDLE getHandle(void) const override;

        // Overriden function
        std::string getId(void) const override;

    private:
        bool m_is_initialized = false;
        boost::asio::io_service m_ioservice;
        boost::asio::ip::tcp::socket m_socket;
        boost::asio::ip::tcp::acceptor m_boost_acceptor;
        AcceptorStrategyAbstractFactory & m_factory;
    };

} /* namespace rg */

#endif /* REACTOR_TESTACCEPTOR_HPP_ */
