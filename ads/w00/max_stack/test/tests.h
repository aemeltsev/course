#ifndef COMPRSTACK_H
#define COMPRSTACK_H

#include <iostream>
#include <random>
#include <type_traits>
#include <vector>
#include <gtest/gtest.h>
#include "comprstack.h"

template< typename T, typename Generator = std::mt19937_64 >
void fill_uniform(const T low,
                             const T high,
                             std::vector<T>& result)
{
    Generator gen{static_cast<typename Generator::result_type>(time(0))};
    if(std::is_integral<T>::value)
    {
        std::uniform_int_distribution<T> dist{low, high};
        for(auto& var: result)
        {
            std::generate(std::begin(var), std::end(var), [&](){ return dist(gen); });
        }
    }
    else if(std::is_floating_point<T>::value)
    {
        std::uniform_real_distribution<T> dist{low, high};
        for(auto& var: result)
        {
            std::generate(std::begin(var), std::end(var), [&](){ return dist(gen); });
        }
    }
}

template< typename T,
         typename Generator = std::mt19937_64,
         typename Comparator = std::greater<T> >
std::pair<std::vector<T>, std::size_t> generate_uniform(const T low,
                                                        const T high,
                                                        const std::size_t size)
{
    std::vector<T> result(size);
    Comparator _comparator;

    fill_uniform<T>(low, high, result);

    std::sort(result.begin(), result.end(), _comparator);

    return std::make_pair(result, result[0]);
}



TEST(MaxStack, FirstStack)
{
    //Arrange
    //Act
    //Assert
}

TEST(MaxStack, SecStack)
{
    //Arrange
    //Act
    //Assert
}

TEST(MaxStack, ThridStack)
{
    //Arrange
    //Act
    //Assert
}

TEST(MinStack, FirstStack)
{
    //Arrange
    //Act
    //Assert
}

TEST(MinStack, SecStack)
{
    //Arrange
    //Act
    //Assert
}

TEST(MinStack, ThridStack)
{
    //Arrange
    //Act
    //Assert
}

#endif //COMPRSTACK_H
