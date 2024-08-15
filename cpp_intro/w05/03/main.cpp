/*
Дано натуральное число N. Выведите слово YES, если число N является точной степенью двойки, или слово NO в противном случае.
Формат входных данных
Вводится натуральное число.
Формат выходных данных
Выведите ответ на задачу.

Sample Input 1:

1

Sample Output 1:

YES

Sample Input 2:

2

Sample Output 2:

YES
*/

#include <iostream>

int main() {
    short n = 0;
    std::cin >> n;
    
    auto out = [&](short n) -> std::string
    {
        for(int x = 1; x <= n; x *= 2) {
            if(x == n) {
                return "YES";
            }
        }
        return "NO";
    };
    
    std::cout << out(n);
    return 0;
}