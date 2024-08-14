/*
Шоколадка имеет вид прямоугольника, разделенного на N×M долек. Шоколадку можно один раз разломить по прямой на две части. Определите, можно ли таким образом отломить от шоколадки ровно K долек.
Формат входных данных
Программа получает на вход три числа: N, M, K
Формат выходных данных
Программа должна вывести одно из двух слов: YES или NO.

Sample Input 1:

4
2
6

Sample Output 1:

YES

Sample Input 2:

2
10
7

Sample Output 2:

NO
*/

#include <iostream>

int main() {
    short n, m, k;
    std::cin >> n;
    std::cin >> m;
    std::cin >> k;
    
    int size = m*n;
    if(k < size && (k % n == 0 || k % m == 0)){
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
  return 0;
}