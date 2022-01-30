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

template <typename Generator=std::mt19937_64>
std::vector<int> generate_uniform(const int low, const int high, const std::size_t size)
{
    std::vector<int> result(size);
    fill_uniform<int>(low, high, result);
    return result;
}

TEST(Sort, Merge)
{
    //Arrenge
    std::vector<int> emmit = generate_uniform(1, 1000, 10);
    auto& comp = emmit;

    collection::adv_sort<int, collection::typeSort::MS> mssort{};

    //Act
    auto result = mssort.sort(emmit);
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
    ASSERT_EQ(*(result.begin()), *(comp.begin()));
    for(std::size_t i = 0; i < result.size(); ++i)
    {
        ASSERT_EQ(result[i], comp[i]);
    }
}

TEST(Sort, Heap)
{
    //Arrenge
    std::vector<int> emmit = generate_uniform(500, 10000, 10);
    auto& comp = emmit;
    collection::adv_sort<int, collection::typeSort::HS> hssort{};

    //Act
    auto result = hssort.sort(emmit);
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
    for(std::size_t i = 0; i < result.size(); ++i)
    {
        ASSERT_EQ(result[i], comp[i]);
    }
}

TEST(Sort, Quick)
{
    //Arrenge
    std::vector<int> emmit = generate_uniform(50, 500, 10);
    auto& comp = emmit;

    collection::adv_sort<int, collection::typeSort::QS> qssort{};

    //Act
    auto result = qssort.sort(emmit);
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
    ASSERT_EQ(*(result.begin()), *(comp.begin()));
    for(std::size_t i = 0; i < result.size(); ++i)
    {
        ASSERT_EQ(result[i], comp[i]);
    }
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
