/*
Шахматный слон ходит по диагонали. Даны две различные клетки шахматной доски, определите, может ли слон попасть с первой клетки на вторую одним ходом.
Формат входных данных
Программа получает на вход четыре числа от 1 до 8 каждое, задающие номер столбца и номер строки сначала для первой клетки, потом для второй клетки.
Формат выходных данных
Программа должна вывести YES, если из первой клетки ходом слона можно попасть во вторую или NO в противном случае.

Sample Input:

4
4
5
5

Sample Output:

YES
*/

#include <iostream>

int main() {
    short a, b, a1, b1;
    std::cin >> a;
    std::cin >> b;
    std::cin >> a1;
    std::cin >> b1;
    
    if(std::abs(a - a1) == std::abs(b - b1)){
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
  return 0;
}