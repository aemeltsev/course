/*
Дано положительное действительное число X. Выведите его первую цифру после десятичной точки.
Формат входных данных
Вводится положительное действительное число.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

1.79

Sample Output:

7
*/

#include <iostream>

int main() {
    double n = 0.;
    std::cin >> n;
    double z = n - static_cast<int>(n);
    std::cout << static_cast<int>(z*100)/10;
	return 0;
}