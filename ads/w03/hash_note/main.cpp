#include <iostream>
#include <string>
#include "nhash.h"

int main()
{
    const std::string ERROR_FOUND = "not found";
    NHash note{512};

    std::size_t count;
    std::cin >> count;

    for(std::size_t i=0; i<count; ++i)
    {
        std::string query;
        std::cin >> query;

        if(std::string("add").compare(query) == 0)
        {
            std::string name;
            int number;
            std::getline(std::cin, name);
            std::cin >> number;
            note.add(number, name);
            continue;
        }
        else if(std::string("find").compare(query) == 0)
        {
            int number;
            std::cin >> number;
            auto result = note.get(number);
            if(result.compare(" ") == 0)
            {
                std::cout << ERROR_FOUND;
            }
            else
            {
                std::cout << result;
            }
            continue;
        }
        else if(std::string("del").compare(query) == 0)
        {
            int number;
            std::cin >> number;
            note.del(number);
            continue;
        }
        else
        {
            std::cout << "Unfound query, return..";
            continue;
        }
    }

    return 0;
}
