#include "tests.hpp"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

/*
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include "sorts.hpp"

int main(int argc, char *argv[])
{
    std::vector<int> emmit{5,4,3,2,1};
    std::vector<int> comp;
    std::copy(emmit.begin(), emmit.end(), std::back_inserter(comp));
    collection::adv_sort<int, collection::typeSort::HS> hssort{};

    //Act
    auto result = hssort.sort(emmit);
    for(auto& var : result)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';
    std::sort(comp.begin(), comp.end());
    for(auto& var : comp)
    {
        std::cout << var << " ";
    }

    std::cout << '\n';

    std::vector<int> input{10,9,8,7,6};
    std::vector<int> out;
    std::copy(input.begin(), input.end(), std::back_inserter(out));
    collection::adv_sort<int, collection::typeSort::MS> mssort{};

    //Act
    auto vart = mssort.sort(input);
    for(auto& var : vart)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';
    std::sort(out.begin(), out.end());
    for(auto& var : out)
    {
        std::cout << var << " ";
    }

    return 0;
}
*/

