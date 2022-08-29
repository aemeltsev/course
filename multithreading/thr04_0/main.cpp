#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>

namespace cv {

std::condition_variable g_bell;
std::condition_variable_any g_door;

class Manager
{
public:
    void ComeToWork()
    {
        std::cout << "Hey security, please open the door!\n";
        g_bell.notify_one();
        std::mutex mutex;
        mutex.lock();
        g_door.wait(mutex);
        mutex.unlock();
    }
};

class Security
{
    static bool m_sector_clear;
    static std::mutex m_sector_mutex;
public:
    static bool SectorClear()
    {
        std::lock_guard<std::mutex> lock(m_sector_mutex);
        return m_sector_clear;
    }

    void NotifyFellows()
    {
        std::lock_guard<std::mutex> lock(m_sector_mutex);
        m_sector_clear = false;
    }

    void WorkHard()
    {
        m_sector_clear = true;
        std::mutex mutex;
        std::unique_lock<std::mutex> lock(mutex);
        while(true)
        {
            if(g_bell.wait_for(lock, std::chrono::seconds(5)) == std::cv_status::timeout){
                std::this_thread::sleep_for(std::chrono::seconds(10));
            }
            else
            {
                NotifyFellows();
                g_door.notify_one();
                std::cout << "Hello Great Manager, your slaves are ready to serve you!\n" << std::endl;
            }
        }
    }
};

bool Security::m_sector_clear;
std::mutex Security::m_sector_mutex;

class Programmer
{
public:
    void WorkHard()
    {
        std::cout << "Let's write some shitcode!\n" << std::endl;
        int i = 0;
        while(true)
        {
            i++;
            i--;
        }
    }
    void PlayStarcraft()
    {
        while(Security::SectorClear())
            ;//Gaming! :)
        WorkHard();// Working :(
    }
};

}

int main()
{
    cv::Manager manager;
    cv::Programmer programmer;
    cv::Security security;

    auto managerCall = [&manager]()
    {
        manager.ComeToWork();
    };
    auto programmerCall = [&programmer]()
    {
        programmer.PlayStarcraft();
    };
    auto securityCall = [&security]()
    {
        security.WorkHard();
    };

    std::thread securityThread(securityCall);
    std::thread programmerThread(programmerCall);
    std::this_thread::sleep_for(std::chrono::minutes(1));
    std::thread managerThread(managerCall);

    managerThread.join();
    programmerThread.join();
    securityThread.join();

    return 0;
}
