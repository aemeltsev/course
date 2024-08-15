/*
По данному числу N распечатайте все целые степени двойки, не превосходящие N, в порядке возрастания.
Формат входных данных

Вводится натуральное число.
Формат выходных данных

Выведите ответ на задачу.

Sample Input:

50

Sample Output:

1 2 4 8 16 32
*/

#include <iostream>
#include <cmath>

int main() {
    short n = 0, i = 0;
    std::cin >> n;
    
    int j = 0;
    while(j <= n/2) {
        j = std::pow(2, i);
        std::cout << j << " ";
        i++;
    }
    return 0;
}