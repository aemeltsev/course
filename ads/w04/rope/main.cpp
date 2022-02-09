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

    std::string str = "hlelowrold";
    rp::Rope rp(str);

    std::cout << rp.find(2) << '\n';
    std::cout << rp.find(5) << '\n';

    return 0;
}
