/*
Сумма цифр трехзначного числа

Дано целое трехзначное число. Найдите сумму его цифр.

Формат входных данных

На вход дается число от 100 до 999.

Формат выходных данных

Выведите одно целое число - ответ на задачу.

Sample Input:

476

Sample Output:

17
*/

#include <iostream>

int main() {
    short num = 0;
    std::cin >> num;
    
    auto a = num % 10;
    //std::cout << a << '\n';
    auto b = (num % 100)/10;
    //std::cout << b << '\n';
    auto c = (num % 1000)/100;
    //std::cout << c << '\n';
    std::cout << a+b+c;
    return 0;
}