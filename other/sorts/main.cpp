#include <iostream>
#include "sorts.hpp"

int main()
{
    std::vector<int> input{5, 4, 3, 2, 1};
    collection::adv_sort<int, collection::typeSort::HS> sr{};

    auto result = sr.sort(input);
    for(auto& var : result)
    {
        std::cout << var << " ";
    }

    return 0;
}
