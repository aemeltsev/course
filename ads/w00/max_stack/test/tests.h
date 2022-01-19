#ifndef COMPRSTACK_TEST_H
#define COMPRSTACK_TEST_H

#include <iostream>
#include <random>
#include <vector>
#include <gtest/gtest.h>
#include <functional>
#include "comprstack.h"

namespace cs_testing {

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

TEST(MaxStack, FirstStack)
{
    //Arrange
    auto emmit = generate_uniform<int>(1, 1000, 100);
    ComprStack<int, std::greater<int>> stack;

    //Act
    for(auto& var : emmit.first)
    {
        stack.cs_push(var);
    }

    //Assert
    ASSERT_EQ(emmit.first.empty(), stack.cs_empty());
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
    ASSERT_EQ(emmit.second, stack.cs_comp());
    auto half_size = emmit.first.size()/2;
    for(auto i = 0; i < half_size; ++i)
    {
        stack.cs_pop();
        emmit.first.pop_back();
    }
    ASSERT_NE(emmit.first[half_size], stack.cs_comp());
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
    ASSERT_EQ(emmit.first[half_size-1], stack.cs_top());
    while(stack.cs_empty() || emmit.first.empty())
    {
        stack.cs_pop();
        emmit.first.pop_back();
    }
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
}

TEST(MaxStack, SecStack)
{
    //Arrange
    auto emmit = generate_uniform<int>(1, 1000000, 100);
    ComprStack<int, std::greater<int>> stack;

    //Act
    //Assert
}

TEST(MaxStack, ThridStack)
{
    //Arrange
    auto emmit = generate_uniform<int>(1, 100, 1000000);
    ComprStack<int, std::greater<int>> stack;

    //Act
    //Assert
}

TEST(MinStack, FirstStack)
{
    //Arrange
    auto emmit = generate_uniform<int, std::less<int>>(1, 100, 1000000);
    ComprStack<int, std::less<int>> stack;

    //Act
    //Assert
}

TEST(MinStack, SecStack)
{
    //Arrange
    auto emmit = generate_uniform<int, std::less<int>>(1, 1000, 100);
    ComprStack<int, std::less<int>> stack;

    //Act
    //Assert
}

TEST(MinStack, ThridStack)
{
    //Arrange
    auto emmit = generate_uniform<int, std::less<int>>(1, 5, 100);
    ComprStack<int, std::less<int>> stack;

    //Act
    //Assert
}

} //cs_testing

#endif //COMPRSTACK_TEST_H
