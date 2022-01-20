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

TEST(MaxStack, SecondStack)
{
    //Arrange
    auto emmit = generate_uniform<int>(1, 100, 1000000);
    ComprStack<int, std::greater<int>> stack;

    //Act
    for(auto& var : emmit.first)
    {
        stack.cs_push(var);
    }

    //Assert
    ASSERT_TRUE(!stack.cs_empty());
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
    ASSERT_EQ(emmit.second, stack.cs_comp());
    while(!stack.cs_empty())
    {
        stack.cs_pop();
    }
    for(auto i = 1; i < emmit.first.size(); ++i)
    {
        if(i % 2 == 0)
        {
            emmit.first.pop_back();
        }
    }
    std::sort(emmit.first.begin(), emmit.first.end(), std::greater<int>());
    ASSERT_TRUE(stack.cs_empty());
    for(auto& var : emmit.first)
    {
        stack.cs_push(var);
    }
    while(stack.cs_empty() || emmit.first.empty())
    {
        stack.cs_pop();
        emmit.first.pop_back();
    }
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
    ASSERT_EQ(emmit.first[0], stack.cs_comp());
    ASSERT_EQ(emmit.first.size(), stack.cs_size());
}

TEST(MinStack, FirstStack)
{
    //Arrange
    constexpr std::size_t SIZE = 100;
    ComprStack<int, std::less<int>> stack;

    //Act
    //Assert
    ASSERT_TRUE(stack.cs_empty());
    for(std::size_t i = SIZE; i > 0; --i)
    {
        stack.cs_push(i);
        ASSERT_EQ(stack.cs_comp(), i);
    }
    ASSERT_EQ(SIZE, stack.cs_size());
    for(std::size_t i = 0; i < SIZE-1; i++)
    {
        ASSERT_EQ(stack.cs_comp(), i+1);
        stack.cs_pop();
    }
    stack.cs_pop();
    ASSERT_TRUE(stack.cs_empty());
}

TEST(MinStack, SecondStack)
{
    //Arrange
    auto emmit = generate_uniform<int, std::less<int>>(1, 100, 1000000);
    ComprStack<int, std::less<int>> stack;

    //Act
    //Assert
}
} //cs_testing

#endif //COMPRSTACK_TEST_H
