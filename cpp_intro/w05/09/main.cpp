/*
Последовательность Фибоначчи определяется так:

F(0) = 0, F(1) = 1, …, F(n) = F(n−1) + F(n−2).

По данному числу N определите N-е число Фибоначчи F(N).
Формат входных данных
Вводится натуральное число N.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

6

Sample Output:

8
*/

#include <iostream>

int fib(int n)
{
    int i = 0;
    int a = 0;
    int b = 1;
    while(i < n){
        int c = a+b;
        a = b;
        b = c;
        //std::cout << a << " " << b << "\n";
        i++;
    }
    return a;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::cout << fib(n);
  return 0;
}