/*
Дано три числа. Упорядочите их в порядке неубывания.
Формат входных данных
Вводятся три числа.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1
2
1

Sample Output:

1 1 2
*/

#include <iostream>

int main() {
    short a, b, c;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    auto min = [&](){
        return std::min(a, std::min(b, c));
    };
    //std::cout << "min= " << min() << '\n';
    auto max = [&](){
        return std::max(a, std::max(b, c));
    };
    //std::cout << "max= " << max() << '\n';
    auto mid = [&](short min, short max){
        if(a == min && b == max || a == max && b == min) {return c;}
        else if(b == min && c == max || b == max && c == min) {return a;}
        else if(c == min && a == max || c == max && a == min) {return b;}
    };
    //std::cout << "mid= " << mid() << '\n';
    std::cout << min() << ' ' << mid(min(), max()) << ' ' << max();
    return 0;
}