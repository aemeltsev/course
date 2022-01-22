#include <iostream>
#include <string>
#include "chhash.h"

int main(int argc, char *argv[])
{
    CHHash note{512};

    std::size_t count;
    std::cin >> count;

    for(std::size_t i=0; i<count; ++i)
    {
        std::string query;
        std::cin >> query;

        if(std::string("add").compare(query) == 0)
        {
            std::string name;
            std::getline(std::cin, name);
            note.add(name);
            continue;
        }
        else if(std::string("find").compare(query) == 0)
        {
            std::string name;
            std::getline(std::cin, name);
            auto result = note.find(name);
            if(result)
            {
                std::cout << "yes" << '\n';
            }
            else
            {
                std::cout << "no" << '\n';
            }
            continue;
        }
        else if(std::string("del").compare(query) == 0)
        {
            std::string name;
            std::getline(std::cin, name);
            note.del(name);
            continue;
        }
        else if(std::string("check").compare(query) == 0)
        {
            std::size_t num;
            std::cin >> num;
            auto result = note.check(num);
            if(!result.empty())
            {
                for(auto& var : result)
                {
                    std::cout << var << " ";
                }
            }
            std::cout << '\n';
        }
        else
        {
            std::cout << "Unfound query, return..";
            continue;
        }
    }
    return 0;
}
