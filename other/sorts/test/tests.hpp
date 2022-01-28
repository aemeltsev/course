#ifndef SORTS_TEST_H
#define SORTS_TEST_H

#include <iostream>
#include <random>
#include <vector>
#include <gtest/gtest.h>
#include <functional>
#include <algorithm>
#include "sorts.hpp"

namespace adv_sort_test
{

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

TEST(Sort, Merge)
{
    //Arrenge
    auto emmit = generate_uniform<int>(1, 1000, 10);
    std::vector<int> comp;
    std::copy(emmit.first.begin(), emmit.first.end(), std::back_inserter(comp));
    collection::adv_sort<int, collection::typeSort::MS> mssort{};

    //Act
    auto result = mssort.sort(emmit.first);
    for(auto& var : result)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';
    std::sort(comp.begin(), comp.end());
    for(auto& var : comp)
    {
        std::cout << var << " ";
    }

    //Assert
    ASSERT_EQ(result.size(), comp.size());
    for(int i = 0; i < result.size(); ++i)
    {
        ASSERT_EQ(result[i], comp[i]);
    }
}

TEST(Sort, Heap)
{
    //Arrenge
    auto emmit = generate_uniform<int>(1, 1000, 10);
    //std::vector<int> comp;
    //std::copy(emmit.first.begin(), emmit.first.end(), std::back_inserter(comp));
    collection::adv_sort<int, collection::typeSort::HS> hssort{};

    //Act
    auto result = hssort.sort(emmit.first);
    for(auto& var : result)
    {
        std::cout << var << " ";
    }
    /*std::cout << '\n';
    std::sort(comp.begin(), comp.end());
    for(auto& var : comp)
    {
        std::cout << var << " ";
    }

    //Assert
    ASSERT_EQ(result.size(), comp.size());
    for(int i = 0, j = 0; i < result.size() && j < comp.size(); ++i, ++j)
    {
        ASSERT_EQ(result[i], comp[i]);
    }
    */
}

TEST(Sort, Quick)
{
    //Arrenge

    //collection::adv_sort<int, collection::typeSort::QS> qssort{};

    //Act

    //Assert
}

TEST(Sort, Tim)
{
    //Arrenge

    //collection::adv_sort<int, collection::typeSort::TS> tssort{};

    //Act

    //Assert
}

} // namespace adv_sort_test

#endif // SORTS_TEST_H
