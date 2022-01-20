#include <iostream>
#include "pqueue.h"

struct Worker
{
    std::size_t _id;
    std::size_t _nextFreeTime;

    Worker (std::size_t id)
        :_id(id)
        ,_nextFreeTime(0)
    {}

    std::size_t get_id() const {return _id;}
    std::size_t get_time() const {return _nextFreeTime;}
};

struct WorkerCompare
{
    bool operator()(Worker& lhp, Worker& rhp) const
    {
        if(lhp.get_time() == rhp.get_time())
        {
            return lhp.get_id() > rhp.get_id();
        }
        else
        {
            return lhp.get_time() > rhp.get_time();
        }
    }
};

std::pair<std::vector<std::size_t>, std::vector<std::size_t>>
assign_job(std::vector<std::size_t>& job, std::size_t nums)
{

    std::vector<std::size_t> assigned_workers(job.size(), 0);
    std::vector<std::size_t> start_times(job.size(), 0);

    PQueue<Worker, WorkerCompare> pq;
    for(std::size_t i=0; i<nums; ++i)
    {
        pq.push(Worker(i));
    }

    for(std::size_t i=0; i<job.size(); ++i)
    {
        Worker freeThread = pq.top();
        pq.pop();

        assigned_workers[i] = freeThread.get_id();
        start_times[i] = freeThread.get_time();

        freeThread._nextFreeTime += job[i];

        pq.push(freeThread);
    }

    return std::make_pair(assigned_workers, start_times);
}

int main()
{
    /* input
     * num thread and vector jobs
     */
    std::size_t num1 = 2;
    std::vector<std::size_t> jobs1{1, 2, 3, 4, 5}; // jobs
    auto pair00 = std::make_pair(num1, jobs1);

    std::size_t num2 = 4;
    std::vector<std::size_t> jobs2{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // jobs
    auto pair01 = std::make_pair(num2, jobs2);

    auto result0 = assign_job(pair00.second, pair00.first);
    auto result1 = assign_job(pair01.second, pair01.first);

    for(auto i=0; i<result0.first.size() && i<result0.second.size(); ++i)
    {
        std::cout << result0.first[i] << " " << result0.second[i] << "\n";
    }

    std::cout << '\n';

    for(auto i=0; i<result1.first.size() && i<result1.second.size(); ++i)
    {
        std::cout << result1.first[i] << " " << result1.second[i] << "\n";
    }
    return 0;
}
