/*
Последовательность Фибоначчи определяется так: 

F(0) = 0, F(1) = 1, …, F(n) = F(n−1) + F(n−2).

Дано натуральное число A. Определите, каким по счету числом Фибоначчи оно является, то есть выведите такое число N, что F(N) = A. Если А не является числом Фибоначчи, выведите число -1.
Формат входных данных
Вводится натуральное число A > 1.
Формат выходных данных
Выведите ответ на задачу.

Sample Input:

8

Sample Output:

6
*/

#include <iostream>

int num_of_fib(int n)
{
    int i = 0;
    int a = 0;
    int b = 1;
    while(true){
        i++;
        int c = a+b;
        a = b;
        b = c;
        //std::cout << a << " " << b << " " << i << "\n";
        if(a == n) break;
        else if(a > n){
            return -1;
        }
    }
    return i;
}

int main() {
    int n = 0;
    std::cin >> n;
    std::cout << num_of_fib(n);
  return 0;
}