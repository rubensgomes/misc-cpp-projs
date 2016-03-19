/*
 * **********************************************************
 * ALL RIGHTS RESERVED,
 * COPYRIGHT (C) Rubens S. Gomes,  2016
 *
 * Author: Rubens S. Gomes
 *
 * File: singleton_creation_strategy.hpp
 *
 * Date:  Mar 8, 2016
 * ********************************************************
 */
#ifndef REACTOR_SINGLETON_CREATION_STRATEGY_HPP_
#define REACTOR_SINGLETON_CREATION_STRATEGY_HPP_

#include "creation_strategy.hpp"

#include <iostream>
#include <memory>

namespace rg
{
    /**
     * This is the singleton creation strategy used to
     * create service handlers.
     *
     * @author Rubens Gomes
     */
    template <typename T>
    class SingletonCreationStrategy : public CreationStrategy
    {
    public:
        // ctor
        SingletonCreationStrategy();

        // dtor
        virtual ~SingletonCreationStrategy();

        // Overriden Function
        ServiceHandler * create(void) override;

    private:
        std::unique_ptr<ServiceHandler> do_create(void);

        std::unique_ptr<ServiceHandler> m_handler;
    };

    template <typename T>
    std::ostream & operator << (std::ostream &, const SingletonCreationStrategy<T> &);
}
#endif /* REACTOR_SINGLETON_CREATION_STRATEGY_HPP_ */
