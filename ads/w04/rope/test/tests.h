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
    std::string a = a_str.substr(0, 13);
    std::string b = a_str.substr(22);
    tree::Rope rp_1(a+b);

    rp_1.insert('_', 13);
    ASSERT_EQ(rp_1.find(13), a_str[13]);
    rp_1.insert('n', 14);
    ASSERT_EQ(rp_1.find(14), a_str[14]);
    rp_1.insert('o', 15);
    ASSERT_EQ(rp_1.find(15), a_str[15]);
    rp_1.insert('t', 16);
    ASSERT_EQ(rp_1.find(16), a_str[16]);
    rp_1.insert('h', 17);
    ASSERT_EQ(rp_1.find(17), a_str[17]);
    rp_1.insert('i', 18);
    ASSERT_EQ(rp_1.find(18), a_str[18]);
    rp_1.insert('n', 19);
    ASSERT_EQ(rp_1.find(19), a_str[19]);
    rp_1.insert('g', 20);
    ASSERT_EQ(rp_1.find(20), a_str[20]);
    rp_1.insert('_', 21);
    ASSERT_EQ(rp_1.find(21), a_str[21]);

    std::string c = b_str.substr(0, 8);
    std::string d = b_str.substr(14);
    tree::Rope rp_2(c+d);

    rp_2.insert('_', 8);
    ASSERT_EQ(rp_2.find(8), b_str[8]);
    rp_2.insert('h', 9);
    ASSERT_EQ(rp_2.find(9), b_str[9]);
    rp_2.insert('e', 10);
    ASSERT_EQ(rp_2.find(10), b_str[10]);
    rp_2.insert('r', 11);
    ASSERT_EQ(rp_2.find(11), b_str[11]);
    rp_2.insert('e', 12);
    ASSERT_EQ(rp_2.find(12), b_str[12]);
    rp_2.insert('_', 13);
    ASSERT_EQ(rp_2.find(13), b_str[13]);

    for(std::size_t i = 0; i < a_str.size(); ++i)
    {
        ASSERT_EQ(rp_1.find(i), a_str[i]);
        ASSERT_EQ(rp_2.find(i), b_str[i]);
    }
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
    tree::Rope rp_1(a_str);
    tree::Rope rp_2(b_str);

    auto a_result = rp_1.to_string();
    auto b_result = rp_2.to_string();

    for(std::size_t i = 0; i < a_str.size(); ++i)
    {
        ASSERT_EQ(a_result[i], a_str[i]);
        ASSERT_EQ(b_result[i], b_str[i]);
    }
}

} //namespace rope_test

#endif //ROPE_TESTS_H
