#ifndef AVLTREE_TEST_H
#define AVLTREE_TEST_H

#include <iostream>
#include <ctime>
#include <gtest/gtest.h>
#include "avltree.h"

namespace avl_test
{

TEST(AVLTree, Insert)
{
    tree::AVLTree<int> tr;
    tr.insert(5);
    tr.insert(2);
    tr.insert(8);
    tr.insert(4);
    tr.insert(9);
    tr.insert(10);
}

TEST(AVLTree, Remove)
{

}

TEST(AVLTree, Find)
{

}

TEST(AVLTree, Begin)
{

}

TEST(AVLTree, End)
{

}

TEST(AVLTree, Size)
{

}

} //namespace avl_test

#endif //AVLTREE_TEST_H
