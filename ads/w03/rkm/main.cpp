#include <iostream>
#include <vector>
#include "rkm.h"

int main()
{

    std::pair<std::string, std::string> input00{"abacaba", "aba"};
    std::pair<std::string, std::string> input01{"testTesttesT", "Test"};
    std::pair<std::string, std::string> input02{"baaaaaaa", "aaaaa"};

    std::string text = "ZtonpqnFzlpvUKZrBbRlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXxtHmTxoLuMbRYsvSpxhtrlvABBlFYmndFzHypOmJyFxjHEPlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXbDiEAvtPlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXRRNoBCUMQVOlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXRLKlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXAYPDKWtVpShhclNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXOJlUlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXglmlNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUXuaOibGlVrwghvNTgLfltIbEdBlgjelFjQkBeFrdEV";
    std::string pattern = "lNoYhXmlwOscxnkTWjsyNJNhgvzMFbxFnbiWuBAGjZQlCRQHjTUX";
    std::pair<std::string, std::string> input03{text, pattern};

    RKM match00(input00.second);
    RKM match01(input01.second);
    RKM match02(input02.second);
    RKM match03(input03.second);

    auto result00 = match00.rkm(input00.first);
    auto result01 = match01.rkm(input01.first);
    auto result02 = match02.rkm(input02.first);
    auto result03 = match03.rkm(input03.first);

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

    for(auto var : result03)
    {
        std::cout << var << " ";
    }
    std::cout << '\n';
    return 0;
}
