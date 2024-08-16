/*
Последовательность состоит из натуральных чисел и завершается числом 0. Определите, какое количество элементов этой последовательности, равны ее наибольшему элементу.
Формат входных данных
Вводится непустая последовательность целых чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания).
Формат выходных данных
Выведите ответ на задачу.

Sample Input 1:

1
7
9
0

Sample Output 1:

1

Sample Input 2:

1
3
3
1
0

Sample Output 2:

2
*/
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    short i = 0, max = 0;
    std::vector<short> v;
    while(true) {
        std::cin >> i;
        if(i != 0) {
            v.push_back(i);
        }
        else {
            break;
        }
    }
    std::sort(v.begin(), v.end());
    
    #if 0
    for(auto itm : v) {
        std::cout << itm << " ";
    }
    #endif
    
    max = *(v.end()-1);
    i = 1;
    for(auto a = v.cbegin(); a != v.cend(); a++) {
        if(*a == max){
            i++;
        }
    }
    std::cout << i-1;
    return 0;
}