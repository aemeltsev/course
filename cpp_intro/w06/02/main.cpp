/*
Даны длины сторон треугольника. Вычислите площадь треугольника.
Формат входных данных
Вводятся три положительных числа.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

3
4
5

Sample Output:

6
*/

#include <iostream>
#include <cmath>

int main() {
    double a = 0;
    double b = 0;
    double c = 0;
    std::cin >> a;
    std::cin >> b;
    std::cin >> c;
    double p = (a + b + c) / 2;
    double s = std::sqrt(p * (p-a) * (p-b) * (p-c));
    std::cout << s;
    return 0;
}