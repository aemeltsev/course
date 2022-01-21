#include <iostream>
#include <vector>
#include <map>
#include "disjointset.h"

int main()
{
    static constexpr std::size_t TABS_COUNT = 5;
    static constexpr std::size_t QUERY_COUNT = 5;

    DisjointSet<std::size_t> fr00;
    DisjointSet<std::size_t> fr01;

    std::map<std::size_t, std::size_t> map00_in;
    std::vector<std::size_t> vec00_in{1, 1, 1, 1, 1};
    std::vector<std::pair<std::size_t, std::size_t>> vec00_union{{3, 5}, {2, 4}, {1, 4}, {5, 4}, {5, 3}};
    std::vector<std::size_t> result00;

    std::size_t tabs = 6;
    std::size_t count = 4;
    std::map<std::size_t, std::size_t> map01_in;
    std::vector<std::size_t> vec01_in{10, 0, 5, 0, 3, 3};
    std::vector<std::pair<std::size_t, std::size_t>> vec01_union{{6, 6}, {6, 5}, {5, 4}, {4, 3}};
    std::vector<std::size_t> result01;

    for(std::size_t i=1; i<=TABS_COUNT; ++i)
    {
        map00_in.insert(std::make_pair(i, vec00_in[i-1]));
    }

    for(std::size_t i=1; i<=tabs; ++i)
    {
        map01_in.insert(std::make_pair(i, vec01_in[i-1]));
    }

    fr00.add_nodes(map00_in);
    fr01.add_nodes(map01_in);

    for(std::size_t j=0; j<QUERY_COUNT; ++j)
    {
        fr00.union_nodes(vec00_union[j].first, vec00_union[j].second);
        std::cout << vec00_union[j].first << " " << vec00_union[j].second << '\n';
        result00.push_back(fr00.max_node_count());
    }

    std::cout << '\n';

    for(auto var : result00)
    {
        std::cout << var << " ";
    }

    std::cout << '\n';

    for(std::size_t j=0; j<count; ++j)
    {
        fr01.union_nodes(vec01_union[j].first, vec01_union[j].second);
        std::cout << vec01_union[j].first << " " << vec01_union[j].second << '\n';
        result01.push_back(fr01.max_node_count());
    }

    std::cout << '\n';

    for(auto& var : result01)
    {
        std::cout << var << " ";
    }

    return 0;
}
