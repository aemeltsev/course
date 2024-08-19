/*
Определите среднее значение всех элементов последовательности, завершающейся числом 0.

Формат входных данных
Вводится последовательность целых чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания).
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1
7
9
0

Sample Output:

5.66666666667
*/

#include <iostream>
#include <iomanip>

int main() {
    int cnt = 0, summ = 0;
    double mean = 0.;
    while(true){
        int j = 0;
        std::cin >> j;
        if(j == 0) break;
        summ += j;
        cnt++;
    }
    mean = static_cast<double>(summ)/cnt;
    std::cout << std::setprecision(12);
    std::cout << mean;
    return 0;
}