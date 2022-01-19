#include <iostream>
#include <set>
#include <vector>
#include "comprstack.h"

std::vector<std::size_t> max_deq_win(const std::vector<std::size_t>& nums, const std::size_t w_size)
{
    std::multiset<std::size_t> mset_inp;
    std::vector<std::size_t> result;

    for(std::size_t i=0; i<w_size; ++i)
    {
        mset_inp.insert(nums[i]); //filling multiset values from nums_{0} to nums_{w_size-1}
    }

    for(std::size_t i=w_size; i<nums.size(); ++i)
    {
        result.push_back(*mset_inp.begin()); //get first element from multiset (it`s large value element from collection) and push it to output array
        mset_inp.erase(mset_inp.find(nums[i-w_size])); //remove the first element from window(equ. window sliding)
        mset_inp.insert(nums[i]); //and insert at the end of the window the next element value (equal to the window slide)
    }
    return result;
}

std::vector<std::size_t> max_stack_win(const std::vector<std::size_t>& input, const std::size_t w_size)
{
    std::vector<std::size_t> result;
    ComprStack<std::size_t> stack_inp;
    ComprStack<std::size_t> stack_out;

    for(const auto& var: input)
    {
        stack_inp.cs_push(var);

        if(stack_inp.cs_size() == w_size)
        {
            while(!stack_inp.cs_empty())
            {
                stack_out.cs_push(stack_inp.cs_top());
                stack_inp.cs_pop();
            }
        }

        if(!stack_out.cs_empty())
        {
            const auto& max_in_flame =
                    (stack_inp.cs_empty()) ? stack_out.cs_comp() : std::max(stack_inp.cs_comp(), stack_out.cs_comp());
            result.push_back(max_in_flame);
            stack_out.cs_pop();
        }
    }
    return result;
}

int main(int argc, char *argv[])
{
    std::vector<std::size_t> result;

    std::vector<std::size_t> in1{1, 5, 7, 22, 1, 8, 33, 10, 12, 11};
    std::size_t w1 = 4;
    std::vector<std::size_t> in2{4, 70, 5, 2, 40, 24, 59, 1, 3, 13, 8, 4, 4, 8};
    std::size_t w2 = 3;
    std::vector<std::size_t> in3{50, 5, 1, 4, 1, 1, 3, 13, 8, 80, 8, 33, 15, 12, 11, 45, 27, 9, 34, 73};
    std::size_t w3 = 5;

    result = max_stack_win(in1, w1);
    if(!result.empty())
    {
        for(auto& var : result)
        {
            std::cout << var << " ";
        }
    }
    else{
        std::cout << "Result is empty" << '\n';
    }
    result.clear();
    std::cout << '\n';

    result = max_stack_win(in2, w2);
    if(!result.empty())
    {
        for(auto& var : result)
        {
            std::cout << var << " ";
        }
    }
    else{
        std::cout << "Result is empty" << '\n';
    }
    result.clear();
    std::cout << '\n';

    result = max_stack_win(in3, w3);
    if(!result.empty())
    {
        for(auto& var : result)
        {
            std::cout << var << " ";
        }
    }
    else{
        std::cout << "Result is empty" << '\n';
    }
    result.clear();
    std::cout << '\n';

    std::vector<std::size_t> out;
    std::vector<std::size_t> input{50, 5, 1, 4, 1, 1, 3, 13, 8, 80, 8, 33, 15, 12, 11, 45, 27, 9, 34, 73};
    std::size_t win = 5;
    out = max_deq_win(input, win);
    if(!out.empty())
    {
        for(auto& var : out)
        {
            std::cout << var << " ";
        }
    }
    else{
        std::cout << "Result is empty" << '\n';
    }
    out.clear();
    std::cout << '\n';

    return 0;
}
