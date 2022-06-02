#include <iostream>
#include <thread>
#include <string>

using namespace std;

int main()
{
    auto func = [](const std::string& first, const std::string& second)
    {
        std::cout << first << second << '\n';
    };

    std::string fr = "Hello, ";
    std::string sc =  "world";

    std::thread thread(func, std::ref(fr), std::ref(sc));
    thread.join();
    return 0;
}
