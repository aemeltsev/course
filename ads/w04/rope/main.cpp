#include "rope.h"
//#include <gtest/gtest.h>

/*
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
*/

int main(int argc, char *argv[])
{

    std::string str = "Only this and nothing more";
    tree::Rope rp;

    for(std::size_t i = 0; i < str.size(); ++i)
    {
        rp.push_back(str[i]);
    }

    for(std::size_t j = 0; j < str.size(); ++j)
    {
        std::cout << rp.find(j) << '\n';
    }

    std::cout << rp.to_string() << '\n';

    return 0;
}
