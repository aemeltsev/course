/*
Напишите программу, определяющую нечётные числа. На вход программы поступает одно целое неотрицательное число. Программа должна вывести 1, если число нечётное, и 0, если число чётное.

Sample Input:

2

Sample Output:

0
*/

#include <stdio.h>

int main() {
    int f;
    scanf("%d", &f);
    if(f % 2 == 0){
        printf("%d", 0);
    }
    else{
        printf("%d", 1);
    }
    return 0;
}