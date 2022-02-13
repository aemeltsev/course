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

    rp.push_back(str[0]);
    rp.push_back(str[1]);

    std::cout << rp.to_string() << '\n';
    //std::cout << rp.find(2) << '\n';
    //std::cout << rp.find(5) << '\n';

    return 0;
}
