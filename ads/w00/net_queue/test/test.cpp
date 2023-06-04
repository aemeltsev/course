#ifndef NETQUEUE_TEST_H
#define NETQUEUE_TEST_H

#include <iostream>
#include <random>
#include <vector>
#include <gtest/gtest.h>
#include <functional>
#include "nqueue.h"

namespace nq_testing {
using NumNetworkQueue = NQueue<int>;

TEST(Numeric_NetworkQueue, one_element_queue)
{
    constexpr int TEST_VAL = 7;
    NumNetworkQueue n_queue{};

    ASSERT_TRUE(n_queue.is_empty());
    n_queue.enqueue(TEST_VAL);
    ASSERT_FALSE(n_queue.is_empty());
    ASSERT_EQ(n_queue.size(), 1);
    ASSERT_EQ(n_queue.top(), TEST_VAL);

    auto val = n_queue.dequeue();

    ASSERT_EQ(val, TEST_VAL);
    ASSERT_TRUE(n_queue.is_empty());
}

TEST(Numeric_NetworkQueue, multiple_element_queue)
{
    constexpr int QUEUE_SIZE = 5;
    NumNetworkQueue n_queue{};

    for(std::size_t i=0; i<QUEUE_SIZE; ++i){
        n_queue.enqueue(static_cast<int>(i));
    }

    ASSERT_EQ(n_queue.size(), QUEUE_SIZE);

    for(std::size_t i=0; i<QUEUE_SIZE; ++i){
        ASSERT_EQ(n_queue.dequeue(), i);
    }

    ASSERT_EQ(n_queue.size(), 0);
}

}

#endif //NETQUEUE_TEST_H
