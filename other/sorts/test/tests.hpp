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
static const std::size_t ARR_SIZE = 1000000;

TEST(Sort, Merge)
{
    //Arrenge
    int* emmit = new int[ARR_SIZE];
    std::vector<int> comp;
    comp.reserve(ARR_SIZE);

    for(std::size_t i=ARR_SIZE, j = 0; i>0 && j<ARR_SIZE; --i, ++j)
    {
        emmit[j] = i;
        comp.push_back(i);
    }

    //Act
    sorting::_merge_sort(emmit, ARR_SIZE);
    std::sort(comp.begin(), comp.end());

    //Assert
    for(std::size_t i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_EQ(emmit[i], comp[i]);
    }
    delete[] emmit;
}

TEST(Sort, Heap)
{
    //Arrenge
    int* emmit = new int[ARR_SIZE];
    std::vector<int> comp;
    comp.reserve(ARR_SIZE);

    for(std::size_t i=ARR_SIZE, j = 0; i>0 && j<ARR_SIZE; --i, ++j)
    {
        emmit[j] = i;
        comp.push_back(i);
    }

    //Act
    sorting::_heap_sort(emmit, ARR_SIZE);
    std::sort(comp.begin(), comp.end());

    //Assert
    for(std::size_t i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_EQ(emmit[i], comp[i]);
    }
    delete[] emmit;
}

TEST(Sort, Quick)
{
    //Arrenge
    int* emmit = new int[ARR_SIZE];
    std::vector<int> comp;
    comp.reserve(ARR_SIZE);

    for(std::size_t i=ARR_SIZE, j = 0; i>0 && j<ARR_SIZE; --i, ++j)
    {
        emmit[j] = i;
        comp.push_back(i);
    }

    //Act
    sorting::_quick_sort(emmit, 1, ARR_SIZE-1);
    std::sort(comp.begin(), comp.end());

    //Assert
    for(std::size_t i = 0; i < ARR_SIZE; ++i)
    {
        ASSERT_EQ(emmit[i], comp[i]);
    }
    delete[] emmit;
}

TEST(Sort, Tim)
{
    //Arrenge
    static const std::size_t TS_SIZE = 100000;
    int* emmit = new int[TS_SIZE];
    std::vector<int> comp;
    comp.reserve(TS_SIZE);

    for(std::size_t i=TS_SIZE, j = 0; i>0 && j<TS_SIZE; --i, ++j)
    {
        emmit[j] = i;
        comp.push_back(i);
    }

    //Act
    sorting::_tim_sort(emmit, TS_SIZE);
    std::sort(comp.begin(), comp.end());

    //Assert
    for(std::size_t i = 0; i < TS_SIZE; ++i)
    {
        ASSERT_EQ(emmit[i], comp[i]);
    }
    delete[] emmit;
}

} // namespace adv_sort_test

#endif // SORTS_TEST_H
