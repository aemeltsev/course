/*
Первая цифра двузначного числа

Дано двузначное число. Выведите его первую цифру (число десятков)

Формат входных данных

На вход дается натуральное двузначное число N.

Формат выходных данных

Выведите одно целое число - ответ на задачу.

Sample Input:

42

Sample Output:

4


*/

#include <iostream>

int main() {
    short num = 0;
    std::cin >> num;
    auto result = (num % 100)/10;
    std::cout << result;
    return 0;
}
