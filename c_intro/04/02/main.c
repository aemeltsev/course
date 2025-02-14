/*
На вход программы поступает натуральное трёхзначное число. Напишите программу, которая выводит сумму цифр этого числа.

Sample Input:

123

Sample Output:

6
*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int f = n / 100 % 10;
    int s = n / 10 % 10;
    int t = n % 10;
    
    printf("%d", f + s + t);
    return 0;
}