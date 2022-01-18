#include <iostream>
#include <stack>
#include <unordered_map>
#include <string>

static bool brackets_catch(const char opeb_br, const char close_br)
{
    static std::unordered_map<char, char> key_brackets{
        {')', '('}, {'}', '{'}, {']', '['}
    };

    return key_brackets[close_br] == opeb_br;
}

std::pair<bool, std::size_t> string_check(const std::string& str)
{
    auto success = false;
    std::size_t pos = 0;
    std::stack<char> stk;
    std::stack<std::size_t> nsize;

    auto itr = str.begin();
    for(std::size_t ind = 1; itr != str.end(); ++itr, ++ind)
    {
        if(*itr == '(' || *itr == '[' || *itr == '{')
        {
            stk.push(*itr);
            nsize.push(ind);
        }
        else
        {
            if(stk.empty() || !brackets_catch(stk.top(), *itr))
            {
                nsize.push(ind);
                pos = nsize.top();
                return std::make_pair(success, pos);
            }

            stk.pop();
            nsize.pop();
        }
    }
    success = stk.empty() && nsize.empty();
    return std::make_pair(success, pos);
}

int main()
{
    std::string str00 = "({})";
    std::string str01 = "({}[()]{}(){)";
    std::string str02 = "({)";

    std::cout << str00 << '\n';
    std::cout << str01 << '\n';
    std::cout << str02 << '\n';

    auto one = string_check(str00);
    auto two = string_check(str01);
    auto tree = string_check(str02);

    std::string out00 = ((one.first && one.second == 0) ? "Correct evaluation" : "Incorrect evaluation");
    std::string out01 = ((two.first && two.second == 0) ? "Correct evaluation" : "Incorrect evaluation");
    std::string out02 = ((tree.first && tree.second == 0) ? "Correct evaluation" : "Incorrect evaluation");

    std::cout << out00 << '\n';
    std::cout << out01 << " " << two.second << '\n';
    std::cout << out02 << " " << tree.second << '\n';

    return 0;
}
