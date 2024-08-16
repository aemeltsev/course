/*
Определите наименьшее расстояние между двумя локальными максимумами последовательности натуральных чисел, завершающейся числом 0. Если в последовательности нет двух локальных максимумов, выведите число 0.

Начальное и конечное значение при этом локальными максимумами не считаются.

Расстоянием считается количество пробелов между элементами. В качестве примера смотрите первый тест.
Формат входных данных
Вводится последовательность целых чисел, оканчивающаяся числом 0 (само число 0 в последовательность не входит, а служит как признак ее окончания).
Формат выходных данных
Выведите ответ на задачу.

Sample Input 1:

1
2
1
1
2
1
2
1
0

Sample Output 1:

2

Sample Input 2:

1
2
3
0

Sample Output 2:

0
*/

#include <iostream>
#include <vector>

int main() {
    
    int loc_max = 0;
    std::vector<int> v;
    std::vector<int> ind;
    while(true) {
        int j = 0;
        std::cin >> j;
        if(j == 0){
            break;
        }
        else{
            v.push_back(j);
        }
    }
    if(v.size() <= 4){
        std::cout << 0;
    }
    else{
        for(int i = 1; i<v.size()-1; ++i){
            int l = v[i-1];
            int m = v[i];
            int r = v[i+1];
            if(m > l && m > r){
                loc_max++;
                ind.push_back(i);
            }
        }
        
        if(ind.size() > 2){
            int min_len = ind[1] - ind[0];
            for(int i = 2; i < ind.size(); ++i){
                min_len = std::min(min_len, (ind[i] - ind[i-1]));
            }
            std::cout << min_len;
        }
        else if(ind.size() == 2){
            std::cout << ind[1] - ind[0];
        }
        else{
            std::cout << 0;
        }
    }
  return 0;
}