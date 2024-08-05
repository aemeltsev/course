/*
Последняя цифра

Дано натуральное число, выведите его последнюю цифру.

Формат входных данных

На вход дается натуральное число N, не превосходящее 10000.

Формат выходных данных

Выведите одно целое число - ответ на задачу.

Sample Input:

753

Sample Output:

3


*/

#include <iostream>

int main() {
    std::size_t num;
    std::cin >> num;
    auto result = num % 10;
    std::cout << result;
    return 0;
}
