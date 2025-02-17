/*
На вход программе подаётся два числа S и E, записанных через пробел. При этом гарантируется, что S≤E.
Программа должна выводить одно случайное число из промежутка [S;E]

Sample Input:

141 273

Sample Output:

233
*/
#include <stdio.h>
#include <stdlib.h>

int main(void){
    int a, b;
    scanf("%d%d", &a, &b);

    int rand_digit = rand() % (b - a + 1) + a;
    printf("%d\n", rand_digit);
    return 0;
}