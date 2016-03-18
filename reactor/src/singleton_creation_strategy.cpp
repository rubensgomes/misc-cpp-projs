/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: singleton_creation_strategy.cpp
 *
 * Date:  Mar 8, 2016
 * ********************************************************
 */

#include "singleton_creation_strategy.hpp"

#include <boost/log/trivial.hpp>

#include <cstddef>

using namespace std;

namespace rg
{

SingletonCreationStrategy::SingletonCreationStrategy()
:m_handler(nullptr)
{
    BOOST_LOG_TRIVIAL(trace) << "SingletonCreationStrategy ["
                             << this
                             << "] constructed.";
}

SingletonCreationStrategy::~SingletonCreationStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "SingletonCreationStrategy ["
                             << this
                             << "] being destructed.";
}

template<class T>
unique_ptr<ServiceHandler> SingletonCreationStrategy::create(
        const HANDLE & handle)
{
    if(m_handler == nullptr)
    {
        T * handler = new T();

        BOOST_LOG_TRIVIAL(trace) << "checking type of T.";

        // check the template "T" class type
        ServiceHandler * type =
            dynamic_cast<ServiceHandler *> (handler);
        if(! type)
        {
            throw new invalid_argument("T is not a ServiceClass");
        }

        m_handler(handler);
    }

    BOOST_LOG_TRIVIAL(trace) << "service handler is opening handle.";
    m_handler->open(handle);
    return m_handler;
}

}
