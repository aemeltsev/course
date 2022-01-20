#ifndef PQUEUE_TEST_H
#define PQUEUE_TEST_H
/*
#include <iostream>
#include <random>
#include <vector>
#include <gtest/gtest.h>
#include <functional>
#include "pqueue.h"

namespace pq_testing {

template <typename T, typename Generator=std::mt19937_64>
void fill_uniform(const T low, const T high, std::vector<T>& result)
{
    Generator gen {static_cast<typename Generator::result_type>(time(0))};
    std::uniform_int_distribution<T> dist {low, high};
    std::generate(std::begin(result), std::end(result), [&] () { return dist(gen); });
}

template <typename Generator=std::mt19937_64, typename Comparator = std::greater<int>>
std::pair<std::vector<int>, std::size_t> generate_uniform(const int low, const int high, const std::size_t size)
{
    std::vector<int> result(size);
    Comparator _comparator;

    fill_uniform<int>(low, high, result);

    std::sort(result.begin(), result.end(), _comparator);

    return std::make_pair(result, result[0]);
}

} //pq_testing
*/
#endif //PQUEUE_TEST_H
