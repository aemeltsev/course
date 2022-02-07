#include <iostream>
#include "avltree.h"

int main(int argc, char *argv[])
{
    AVLTree<int> tr;
    tr.insert(5);
    tr.insert(2);
    tr.insert(8);
    tr.insert(4);
    tr.insert(9);
    tr.insert(10);

    std::cout << tr.size() << '\n';

    return 0;
}
