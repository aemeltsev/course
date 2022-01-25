/*#include <iostream>
#include "spltree.h"

int main(int argc, char *argv[])
{
    splay::SPLAYT stree;

    int32_t quest;
    std::cin >> quest;

    for(int32_t ind=0; ind < quest; ++ind)
    {
        char symb;
        std::cin >> symb;

        switch(symb)
        {
        case '+':{
            int32_t var;
            std::cin >> var;
            stree.insert(var % splay::limit);
        }break;

        case '-':{
            int32_t var;
            std::cin >> var;
            stree.erase(var % splay::limit);
        }break;

        case '?':{
            int32_t var;
            std::cin >> var;
            std::cout << (stree.find(var % splay::limit) ? "found" : "not found");
        }break;

        case 's':{
            int32_t x, y;
            std::cin >> x >> y;
            auto result = stree.sum(x, y);
            std::cout << result;
        }

        }
    }
}
*/
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
