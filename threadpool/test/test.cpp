#define BOOST_TEST_MODULE ThreadPool Test Suite 
#include <boost/test/included/unit_test.hpp> 

#include "thread_pool.hpp"

BOOST_AUTO_TEST_CASE(first_test) 
{
    ThreadPool * pool = ThreadPool::instance();
    int nr_threads = pool->getTotalThreads();

    BOOST_TEST(nr_threads);
    BOOST_TEST(nr_threads == THREAD_POOL_SIZE);

}
