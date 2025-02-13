// Программа должна выводить на экран информацию о координатах

#include <stdio.h>

int main() {
    int n_g, w_g;
    double n_m, w_m, n_s, w_s;
    n_g = 51, w_g = 0;
    n_m = 31, w_m = 9;
    n_s = 25.48, w_s = 29.93;
    
    printf("S.Holmes:\n");
    printf("%-2dgrad %2.0f\'%.2f\" N\n", n_g, n_m, n_s);
    printf("%-2dgrad %2.0f\'%.2f\" W", w_g, w_m, w_s);
    return 0;
}