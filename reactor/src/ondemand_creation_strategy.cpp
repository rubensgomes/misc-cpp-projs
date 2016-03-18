/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: ondemand_creation_strategy.cpp
 *
 * Date:  Mar 8, 2016
 * ********************************************************
 */
#include "ondemand_creation_strategy.hpp"

#include <boost/log/trivial.hpp>

using namespace std;

namespace rg
{

OnDemandCreationStrategy::OnDemandCreationStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemandCreationStrategy ["
                             << this
                             << "] constructed.";
}

OnDemandCreationStrategy::~OnDemandCreationStrategy()
{
    BOOST_LOG_TRIVIAL(trace) << "OnDemandCreationStrategy ["
                             << this
                             << "] being destructed.";
}

template<class T>
std::unique_ptr<ServiceHandler> OnDemandCreationStrategy::create(
        const HANDLE & handle)
{
    T * handler = new T();

    BOOST_LOG_TRIVIAL(trace) << "checking type of T.";

    // check the template "T" class type
    ServiceHandler * type =
            dynamic_cast<ServiceHandler *> (handler);
    if(! type)
    {
        throw new std::invalid_argument("T is not a ServiceClass");
    }

    unique_ptr<ServiceHandler> p (handler);

    BOOST_LOG_TRIVIAL(trace) << "service handler is opening handle.";

    p->open(handle);
    return p;
}

}
