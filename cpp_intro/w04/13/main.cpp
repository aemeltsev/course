/*
Есть две коробки, первая размером A1×B1×C1, вторая размером A2×B2×C2. Определите, можно ли разместить одну из этих коробок внутри другой, при условии, что поворачивать коробки можно только на 90 градусов вокруг ребер.
Формат входных данных
Программа получает на вход числа A1, B1, C1, A2, B2, C2.
Формат выходных данных
Программа должна вывести одну из следующих строчек:
Boxes are equal, если коробки одинаковые,
The first box is smaller than the second one, если первая коробка может быть положена во вторую,
The first box is larger than the second one, если вторая коробка может быть положена в первую,
Boxes are incomparable, во всех остальных случаях.

Sample Input 1:

1
2
3
3
2
1

Sample Output 1:

Boxes are equal

Sample Input 2:

2
2
3
3
2
1

Sample Output 2:

The first box is larger than the second one
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<short> box1(3, 0);
    std::vector<short> box2(3, 0);
    std::cin >> box1[0];
    std::cin >> box1[1];
    std::cin >> box1[2];
    std::cin >> box2[0];
    std::cin >> box2[1];
    std::cin >> box2[2];
    std::sort(box1.begin(), box1.end());
    std::sort(box2.begin(), box2.end());
    short length1 = box1[0]; // длинна коробки 1
    short width1 = box1[2]; // ширина коробки 1
    short height1 = box1[1]; // высота коробки 1
    short length2 = box2[0]; // длинна коробки 2
    short width2 = box2[2]; // ширина коробки 2
    short height2 = box2[1]; // высота коробки 2
    
    // std::cout << "length box 1 - " << length1 << " " << "width box 1 - " << width1 << " " << "height box 1 - " << height1 << '\n';
    // std::cout << "length box 2 - " << length2 << " " << "width box 2 - " << width2 << " " << "height box 2 - " << height2 << '\n';
    if(box1[0] == box2[0] && box1[1] == box2[1] && box1[2] == box2[2]) {
        std::cout << "Boxes are equal";
    }
    else if((length2 < length1 && width2 <= width1 && height2 <= height1) || (width2 < width1 && length2 <= length1 && height2 <= height1) || (height2 < height1 && width2 <= width1 && length2 <= length1)) {
        std::cout << "The first box is larger than the second one";
    }
    else if((length1 < length2 && width1 <= width2 && height1 <= height2) || (width1 < width2 && length1 <= length2 && height1 <= height2) || (height1 < height2 && width1 <= width2 && length1 <= length2)) {
        std::cout << "The first box is smaller than the second one";
    }
    else {
        std::cout << "Boxes are incomparable";
    }
    
  return 0;
}