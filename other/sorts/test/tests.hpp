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
static const std::size_t ARR_SIZE = 10;

TEST(Sort, Merge)
{
    //Arrenge
    int emmit[ARR_SIZE];
    std::vector<int> comp;
    comp.reserve(ARR_SIZE);

    for(std::size_t i=ARR_SIZE, j = 0; i>0 && j<ARR_SIZE; --i, ++j)
    {
        emmit[j] = i;
        comp.push_back(i);
    }

    //Act
    collection::_merge_sort(emmit, ARR_SIZE);
    std::sort(comp.begin(), comp.end());

    /*for(std::size_t i=0; i<ARR_SIZE; ++i)
    {
        std::cout << emmit[i] << " ";
    }

    std::cout << '\n';

    for(auto& var : comp)
    {
        std::cout << var << " ";
    }*/

    //Assert
    for(std::size_t i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_EQ(emmit[i], comp[i]);
    }
}

TEST(Sort, Heap)
{
/*    //Arrenge
    std::vector<int> emmit = generate_uniform(500, 10000, 100);
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
    }*/
}

TEST(Sort, Quick)
{
/*    //Arrenge
    std::vector<int> emmit = generate_uniform(50, 500, 10);
    auto& comp = emmit;

    collection::adv_sort<int, collection::typeSort::QS> qssort{};

    //Act
    auto result = qssort.sort(emmit);
//    for(auto& var : result)
//    {
//        std::cout << var << " ";
//    }
//    std::cout << '\n';
    std::sort(comp.begin(), comp.end());
//    for(auto& var : comp)
//    {
//        std::cout << var << " ";
//    }

    //Assert
    ASSERT_EQ(*(result.begin()), *(comp.begin()));
    for(std::size_t i = 0; i < result.size(); ++i)
    {
        ASSERT_EQ(result[i], comp[i]);
    }*/
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
