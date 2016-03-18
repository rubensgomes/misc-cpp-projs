/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: ondemand_creation_strategy.hpp
 *
 * Date:  Mar 8, 2016
 * ********************************************************
 */
#ifndef REACTOR_ONDEMAND_CREATION_STRATEGY_HPP_
#define REACTOR_ONDEMAND_CREATION_STRATEGY_HPP_

#include "creation_strategy.hpp"

#include <memory>

namespace rg
{
    /**
     * This is the On demand creation strategy used to create
     * service handlers.   This class will instantiate a new
     * instance of Service Handler every time.
     *
     * @author Rubens Gomes
     */
    class OnDemandCreationStrategy: public CreationStrategy
    {
    public:
        // ctor
        OnDemandCreationStrategy();

        // dtor
        virtual ~OnDemandCreationStrategy();

        // Overriden Function
        template<class T>
        std::unique_ptr<ServiceHandler> create(const HANDLE &);
    };
}
#endif /* REACTOR_ONDEMAND_CREATION_STRATEGY_HPP_ */
