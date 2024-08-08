/*
Покупка пирожков

Пирожок в столовой стоит A рублей и B копеек. Определите, сколько рублей и копеек нужно заплатить за N пирожков.


Формат входных данных

Программа получает на вход три числа: A, B, N - целые, положительные, не превышают 10000.

Формат выходных данных

Программа должна вывести два числа через пробел: стоимость покупки в рублях и копейках.

Sample Input 1:

10
15
2

Sample Output 1:

20 30

Sample Input 2:

2
50
4

Sample Output 2:

10 0


*/

#include <iostream>

int main() {
    short a, b, n;
    std::cin >> a;
    std::cin >> b;
    std::cin >> n;
    
    
    auto result_cop = b*n;
    auto result_rub = a*n;
    auto carry = (result_cop/100);
    std::cout << result_rub + carry << ' ' << result_cop%100;
    //std::cout << '\n' << carry;
    return 0;
}
