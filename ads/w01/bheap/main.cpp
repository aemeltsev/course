#include <iostream>
#include "bheap.h"

int main()
{
    std::vector<int> vec{4, 6, 5, 10, 3, 8};
    BHeap<int> b_heap1{7, 8, 5, 4, 6, 13, 10, 9, 15, 17};
    BHeap<int> b_heap2(vec);
    BHeap<int> b_heap3{5, 4, 3, 2, 1};
    BHeap<int> b_heap4{1, 2, 3, 4, 5};

    auto data1 = b_heap1.get_tech_detail();
    auto data2 = b_heap2.get_tech_detail();
    auto data3 = b_heap3.get_tech_detail();
    auto data4 = b_heap4.get_tech_detail();

    while(!b_heap1.is_empty())
    {
        std::cout << b_heap1.top() << " ";
        b_heap1.pop();
    }
    std::cout << "\n";
    for(auto& var : data1)
    {
        std::cout << var.first << ":" << var.second << " ";
    }
    std::cout << "\n";

    while(!b_heap2.is_empty())
    {
        std::cout << b_heap2.top() << " ";
        b_heap2.pop();
    }
    std::cout << "\n";
    for(auto& var : data2)
    {
        std::cout << var.first << ":" << var.second << " ";
    }
    std::cout << "\n";

    while(!b_heap3.is_empty())
    {
        std::cout << b_heap3.top() << " ";
        b_heap3.pop();
    }
    std::cout << "\n";
    for(auto& var : data3)
    {
        std::cout << var.first << ":" << var.second << " ";
    }
    std::cout << "\n";

    while(!b_heap4.is_empty())
    {
        std::cout << b_heap4.top() << " ";
        b_heap4.pop();
    }
    std::cout << "\n";
    for(auto& var : data4)
    {
        std::cout << var.first << ":" << var.second << " ";
    }
    std::cout << "\n";

    return 0;
}
