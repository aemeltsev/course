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

TEST(RopeTest, Splay)
{

}

TEST(RopeTest, Insert)
{

}

TEST(RopeTest, Find)
{
    tree::Rope rp(a_str);

    ASSERT_EQ(rp.find(1), a_str[0]);
    //ASSERT_EQ(rp->find(2), a_str[1]);
   // ASSERT_EQ(rp->find(3), a_str[2]);
    //ASSERT_EQ(rp->find(4), a_str[3]);
    //ASSERT_EQ(rp->find(5), a_str[4]);
    //ASSERT_EQ(rp->find(6), a_str[5]);
   // ASSERT_EQ(rp->find(7), a_str[6]);
    //ASSERT_EQ(rp->find(8), a_str[7]);
    //ASSERT_EQ(rp->find(9), a_str[8]);
   // ASSERT_EQ(rp->find(10), a_str[9]);
   // ASSERT_EQ(rp->find(11), a_str[10]);
   // ASSERT_EQ(rp->find(12), a_str[11]);
  //  ASSERT_EQ(rp->find(13), a_str[12]);
}

TEST(RopeTest, ToString)
{

}

} //namespace rope_test

#endif //ROPE_TESTS_H
