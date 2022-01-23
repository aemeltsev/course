#include <iostream>
#include <vector>
#include "rkm.h"

int main()
{

    std::pair<std::string, std::string> input00{"abacaba", "aba"};
    std::pair<std::string, std::string> input01{"testTesttesT", "Test"};
    std::pair<std::string, std::string> input02{"baaaaaaa", "aaaaa"};

    RKM match00(input00.first);
    RKM match01(input01.first);
    RKM match02(input02.first);

    auto result00 = match00.rkm(input00.second);
    auto result01 = match01.rkm(input01.second);
    auto result02 = match02.rkm(input02.second);

    for(auto var : result00)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';

    for(auto var : result01)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';

    for(auto var : result02)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';


    return 0;
}
