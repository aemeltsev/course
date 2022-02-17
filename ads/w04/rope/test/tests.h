#ifndef ROPE_TESTS_H
#define ROPE_TESTS_H

#include <iostream>
#include <ctime>
#include <string>
#include <gtest/gtest.h>
#include "rope.h"

namespace rope_test
{

static std::string a_str = "Only_this_and_nothing_more";
static std::string b_str = "Nameless_here_for_evermore";

TEST(RopeTest, Remove)
{

}

TEST(RopeTest, Insert)
{

}

TEST(RopeTest, Push_Back)
{
    tree::Rope rp;

    std::size_t size = a_str.size()/2;
    ASSERT_EQ(rp.size(), 0);
    for(std::size_t i = 0; i < size; ++i)
    {
        rp.push_back(a_str[i]);
    }
    ASSERT_EQ(rp.size(), size);
    for(std::size_t j = size; j < a_str.size(); ++j)
    {
        rp.push_back(a_str[j]);
    }
    ASSERT_EQ(rp.size(), a_str.size());
}

TEST(RopeTest, Find)
{
    tree::Rope rp(a_str);
    std::size_t asize = a_str.size();

    for(std::size_t i = 0; i < asize; ++i)
    {
        ASSERT_EQ(rp.find(i), a_str[i]);
    }

    tree::Rope st(b_str);
    std::size_t bsize = b_str.size();

    for(std::size_t i = 0; i < bsize; ++i)
    {
        ASSERT_EQ(st.find(i), b_str[i]);
    }
}

TEST(RopeTest, ToString)
{

}

} //namespace rope_test

#endif //ROPE_TESTS_H
