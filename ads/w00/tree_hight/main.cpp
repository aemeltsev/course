#include <iostream>
#include <vector>

std::size_t tree_height(std::vector<int>& parent)
{
    static constexpr int ROOT_NODE = -1;
    auto result_height = 0;

    // cycle on parent array node
    for(auto i = 0; i < parent.size(); ++i)
    {
        auto parent_node = i;
        auto current_height = 1;
        while(parent[parent_node] != ROOT_NODE)
        {
            ++current_height;
            parent_node = parent[parent_node];
        }

        result_height = std::max(result_height, current_height);
    }
    return result_height;
}

int main()
{
    const std::string TXT_OUT = "The height of the binary tree is ";

    std::vector<int> parent00{-1, 0, 0, 1, 2, 2, 4, 4};
    std::vector<int> parent01{4, -1, 4, 1, 1};
    std::vector<int> parent02{-1, 0, 4, 0, 3};

    std::cout << TXT_OUT << tree_height(parent00) << '\n';
    std::cout << TXT_OUT << tree_height(parent01) << '\n';
    std::cout << TXT_OUT << tree_height(parent02) << '\n';

    return 0;
}
