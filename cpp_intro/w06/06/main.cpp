/*
Дана последовательность натуральных чисел x1, x2, ..., xn.
Определите стандартное отклонение для данной последовательности натуральных чисел, завершающейся числом 0.

Формат входных данных
Вводится последовательность натуральных чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания). В последовательности не менее двух чисел до 0.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1
7
9
0

Sample Output:

4.16333199893
*/

#include <iostream>
#include <iomanip>
#include <cmath>

int main() {
    int cnt = 0;
    double summ1 = 0., summ2 = 0.;
    double mean = 0.;
	long long j = 0;
    while(true){
        std::cin >> j;
        if(j == 0){break;}
        else{
            summ1 += (j * j);
            summ2 += j; 
            cnt++;
        }
    }
    double tmp = (summ1 - ((summ2 * summ2) / cnt)) / (cnt - 1);
    mean = std::sqrt(tmp);
    std::cout << std::fixed << std::setprecision(11) << mean;
    return 0;
}