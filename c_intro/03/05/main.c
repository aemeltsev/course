/*
В следующей программе переменные объявлены внутри программы. Исправьте её таким образом, чтобы значения переменных a, b, и с считывались функцией scanf.

Sample Input:

10 7 2

Sample Output:

15
*/

#include <stdio.h> 
int main(void) {
    int a, b, res, c, var;
    var = scanf("%d%d%d", &a, &b, &c);
    res = a + b;
    res = res - c;
    printf("%d\n", res);
    return 0;
}