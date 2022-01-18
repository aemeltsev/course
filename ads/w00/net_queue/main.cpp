#include <vector>
#include "nqueue.h"

int main()
{
    static constexpr int ERROR_TIME = -1;

    std::size_t size = 1;
    std::size_t pack_count = 2;
    std::vector<std::pair<std::size_t, std::size_t>> emitter{{0,1},{0,1}};

    std::size_t cpu_time = 0;
    NQueue<std::size_t> queue;
    std::vector<int> result;

    for(auto i =0; i < pack_count; ++i)
    {
        auto arrival = emitter[i].first;
        auto duration = emitter[i].second;

        while(!queue.is_empty() && queue.top() <= arrival)
        {
            queue.dequeue();
        }

        if(cpu_time < arrival)
        {
            result.push_back(arrival);
            cpu_time = arrival + duration;
            queue.enqueue(cpu_time);
        }
        else if(queue.size() < size)
        {
            result.push_back(cpu_time);
            cpu_time += duration;
            queue.enqueue(cpu_time);
        }
        else
        {
            result.push_back(ERROR_TIME);
        }
    }

    for(auto& var : result)
    {
        std::cout << var << '\n';
    }

    return 0;
}
