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

template <typename T>
ostream & operator << (ostream & out, const SingletonCreationStrategy<T> & rhs)
{
    out << rhs << endl;
    return (out);
}

template <typename T>
SingletonCreationStrategy<T>::SingletonCreationStrategy()
:m_handler(nullptr)
{
    BOOST_LOG_TRIVIAL(trace) << "SingletonCreationStrategy ["
                             << this
                             << "] constructed.";
}

template <typename T>
SingletonCreationStrategy<T>::~SingletonCreationStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "SingletonCreationStrategy ["
                             << this
                             << "] being destructed.";
}

template <typename T>
ServiceHandler * SingletonCreationStrategy<T>::create(void)
{
    BOOST_LOG_TRIVIAL(trace) << "SingletonCreationStrategy entering create ...";

    if(m_handler)
    {
        BOOST_LOG_TRIVIAL(trace) << "returning previously created m_handler ...";
        return(m_handler.get());
    }
    else
    {
        BOOST_LOG_TRIVIAL(trace) << "creating m_handler ...";
        return(do_create());
    }
}

template <typename T>
unique_ptr<ServiceHandler> SingletonCreationStrategy<T>::do_create(void)
{
    BOOST_LOG_TRIVIAL(trace) << "checking typename T.";

    T * handler = new T();

    // check the template "T" class type
    ServiceHandler * type =
        dynamic_cast<ServiceHandler *> (handler);
    if(! type)
    {
        delete handler;
        throw new invalid_argument("T is not a ServiceClass");
    }

    m_handler(handler);
    return m_handler.get();
}

}
