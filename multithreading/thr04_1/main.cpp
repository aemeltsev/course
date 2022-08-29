#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>

namespace pp {

std::condition_variable g_condition;
std::mutex g_mutex;
bool flag = false;

void print_ping(int count)
{
    std::unique_lock<std::mutex> lock(g_mutex);
    for(auto i=0; i<count; ++i)
    {
        g_condition.wait(lock, [](){return flag ? true : false;});
        std::cout << "\nPING in " << std::this_thread::get_id() << "\n";
        flag = !flag;
        g_condition.notify_one();
    }
}

void print_pong(int count)
{
    std::unique_lock<std::mutex> lock(g_mutex);
    for(auto i=0; i<count; ++i)
    {
        g_condition.wait(lock, [](){return !flag ? true : false;});
        std::cout << "\nPONG in " << std::this_thread::get_id() << "\n";
        flag = !flag;
        g_condition.notify_one();
    }
}
}

int main()
{
    int pp_count = 10;
    std::thread ping_thread(std::ref(pp::print_ping), std::ref(pp_count));
    std::thread pong_thread(std::ref(pp::print_pong), std::ref(pp_count));
    ping_thread.join();
    pong_thread.join();
    return 0;
}
