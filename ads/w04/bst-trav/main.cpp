#include <iostream>
#include <vector>
#include <tuple>

#include "bst.h"
/*
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
*/

int main()
{
    using _tn = std::tuple<int, int, int>;
    using _vector_tn = std::vector<_tn>;

    _vector_tn in;

    in.push_back(std::tuple<int, int, int>(4, 1, 2));
    in.push_back(std::tuple<int, int, int>(2, 3, 4));
    in.push_back(std::tuple<int, int, int>(5, -1, -1));
    in.push_back(std::tuple<int, int, int>(1, -1, -1));
    in.push_back(std::tuple<int, int, int>(3, -1, -1));

    bst::BST<int> bt(in);
    auto inorder = bt.get_in_order();
    auto preorder = bt.get_pre_order();
    auto postorder = bt.get_post_order();

    if(bt.is_valid())
    {
        std::cout << "yes, it's valid binary tree" << '\n';
    }
    else
    {
        std::cout << "sorry, it's no valid binary tree" << '\n';
    }

    for(auto& var : inorder)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';

    for(auto& var : preorder)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';

    for(auto& var : postorder)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';

    return 0;
}
