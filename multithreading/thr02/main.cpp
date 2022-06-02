#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <mutex>
#include <list>
#include <limits>
#include <exception>

namespace wh {

class WarehouseException : public std::exception
{
protected:
    const std::string m_error;
public:
    explicit WarehouseException(std::string&& str)
        :m_error(std::move(str))
    {}

    const char* what() const noexcept override
    {
        return (m_error.c_str());
    }
};

class WarehouseEmpty : public WarehouseException
{
public:
    explicit WarehouseEmpty(std::string&& str)
        :WarehouseException(std::move(str))
    {}
};

unsigned short c_special_item =
    std::numeric_limits<unsigned short>::max();

class Warehouse
{
    std::list<unsigned short> m_store;
public:
    void AcceptItem(unsigned short item)
    {
        m_store.push_back(item);
    }

    unsigned short HandLastItem()
    {
        if(m_store.empty()){
            throw WarehouseEmpty("Warehouse is empty!\n");
            return -1;
        }
        unsigned short item = m_store.front();
        if(item != c_special_item){
            m_store.pop_front();
        }
        return item;
    }
};

Warehouse g_first_wh;
Warehouse g_second_wh;
std::timed_mutex g_first_mutex;
std::mutex g_second_mutex;

}

int main()
{
    auto suplier = []()
    {
        for(unsigned short i = 0, j = 0; i < 10 || j < 10;)
        {
            if(i < 10 && wh::g_first_mutex.try_lock())
            {
                wh::g_first_wh.AcceptItem(i);
                i++;
                wh::g_first_mutex.unlock();
            }
            if(j < 10 && wh::g_second_mutex.try_lock())
            {
                wh::g_second_wh.AcceptItem(j);
                j++;
                wh::g_second_mutex.unlock();
            }
            std::this_thread::yield();
        }

        std::lock_guard<std::timed_mutex> first_guard(wh::g_first_mutex);
        std::lock_guard<std::mutex> second_mutex(wh::g_second_mutex);

        wh::g_first_wh.AcceptItem(wh::c_special_item);
        wh::g_second_wh.AcceptItem(wh::c_special_item);
    };

    auto consumer = []()
    {
        while(true)
        {
            unsigned short item = 0;
            try
            {
                std::lock_guard<std::timed_mutex> guard(wh::g_first_mutex);
                item = wh::g_first_wh.HandLastItem();
            }
            catch (wh::WarehouseEmpty&)
            {
                throw wh::WarehouseEmpty("Warehouse is empty!\n");
            }

            if(item != wh::c_special_item) break;
            std::cout << "Got new item: " << item << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }

    };

    auto impatient_consumer = []()
    {
        while(true)
        {
            unsigned short item = 0;
            if(wh::g_first_mutex.try_lock_for(std::chrono::seconds(2)))
            {
                try
                {
                    std::lock_guard<std::timed_mutex> guard(wh::g_first_mutex,
                                                            std::adopt_lock);
                    item = wh::g_first_wh.HandLastItem();
                }
                catch(const wh::WarehouseEmpty&)
                {
                    throw wh::WarehouseEmpty("Warehouse is empty! I'm mad!!!11\n");
                }
            }
            else
            {
                std::cout << "First warehouse is always busy!!!\n";
                try
                {
                    std::lock_guard<std::mutex> guard(wh::g_second_mutex);
                    item = wh::g_second_wh.HandLastItem();
                }
                catch(const wh::WarehouseEmpty&)
                {
                    throw wh::WarehouseEmpty("2nd warehouse is empty!!!!11\n");
                }
            }

            if(item == wh::c_special_item) break;

            std::cout << "At last I got new item: " << item << "!\n";
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    };

    std::thread supplier_thread(suplier);
    std::thread consumer_thread(consumer);
    std::thread impatient_consumer_thread(impatient_consumer);

    supplier_thread.join();
    consumer_thread.join();
    impatient_consumer_thread.join();

    return 0;
}
