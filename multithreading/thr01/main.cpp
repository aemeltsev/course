#include <iostream>
#include <thread>
#include <string>
#include <chrono>

#include <Windows.h>

using namespace std;

int main()
{
    auto func = [](const std::string& first, const std::string& second)
    {
        std::cout << first << second << '\n';
    };

    auto min = std::chrono::system_clock::now() + std::chrono::minutes(3);

    std::string fr = "Hello, ";
    std::string sc =  "world\n";

    std::thread thread(func, std::ref(fr), std::ref(sc));
    std::this_thread::sleep_until(min);
    std::this_thread::sleep_for(std::chrono::minutes(3));

    std::cout << "Id from WinAPI: 0x" << std::hex << ::GetCurrentThreadId()
              << "\n";
    std::cout <<"Id from C++ API: 0x"<< std::hex << std::this_thread::get_id()
              << "\n";

    thread.join();
    return 0;
}
