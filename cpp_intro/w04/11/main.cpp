/*
Яша плавал в бассейне размером N×M метров и устал. В этот момент он обнаружил, что находится на расстоянии X метров от одного из длинных бортиков (не обязательно от ближайшего) и Y метров от одного из коротких бортиков. Какое минимальное расстояние должен проплыть Яша, чтобы выбраться из бассейна на бортик?
Формат входных данных
Программа получает на вход числа N, M, X, Y.
Формат выходных данных

Программа должна вывести число метров, которое нужно проплыть Яше до бортика.

Sample Input:

23
52
8
43

Sample Output:

8
*/

#include <iostream>

int main() {
    short n, m, x, y;
    std::cin >> n;
    std::cin >> m;
    std::cin >> x;
    std::cin >> y;
    short long_border = std::max(n, m);
    // std::cout << "long_border= " << long_border << '\n';
    short short_border = std::min(n, m);
    // std::cout << "short_border= " << short_border << '\n';
    short a = std::min(long_border - y, short_border - x);
    short b = std::min(x, y);
    auto result = std::min(a, b);
    std::cout << result;
  return 0;
}