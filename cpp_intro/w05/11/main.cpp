/*
Дана последовательность натуральных чисел, завершающаяся числом 0. Определите, какое наибольшее число подряд идущих элементов этой последовательности равны друг другу. Если не нашлось ни одной пары, тройки и т.д. элементов, равных друг другу, то программа должна вывести число 1.
Формат входных данных
Вводится последовательность натуральных чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания).
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1
7
7
9
1
0

Sample Output:

2
*/

#include <iostream>
#include <algorithm> 

int main() {
    
    int maxi = 0, indx = 0, var = 0;
    std::cin >> var;
    indx++;
    maxi = indx;
    while(true) {
        int j = 0;
        std::cin >> j;
        if(var == j){
            indx++;
        }
        else{
            maxi = std::max(indx, maxi);
            var = j;
            indx = 1;
        }
        if(j == 0) break;
    }
    std::cout << maxi;
    
  return 0;
}