#include <iostream>
#include <fstream>
#include "list.h"

template <typename T>
typename dlist::list<T>::iterator find(dlist::list<T>& theList, const T& item) {
  typename dlist::list<T>::iterator iter = theList.begin();
  while(iter != theList.end()) {
    if(*iter == item)
      return iter;
    iter++;
  }
  return iter;
}

int main() {
  dlist::list<int> l{};

  std::ifstream inf("data.txt", std::ios_base::in);

  // Read a list of data items from the file
  // and insert them in the list.
  int x, i = 0;
  while(inf >> x) {
    std::cout << i++ << ": " << x << '\n';
    l.push_back(x);
  }
  std::cout << '\n' << "size: " <<  l.size() << '\n';

  // Find all of the numbers from 1 to 19 that do not
  // appear in the list, and print them.
  std::cout << "find elements:\n";
  for(int n = 1;n < 20;n++) {
    if(find(l,n) == l.end())
      std::cout << n << " - exist" << '\n';
    else
      std::cout << n << " - no exist" << '\n';
  }
  std::cout << '\n';

  // Remove all numbers of the form 1 + 3*k from the list
  std::cout << "remove elements:\n";
  for(int n = 1;n < 20;n = n + 3) {
    dlist::list<int>::iterator itr = find(l,n);
    if(itr != l.end()) {
      std::cout << "element: " << *itr << '\n';
      l.erase(itr);
    }
  }
  std::cout << '\n' << "size: " <<  l.size() << '\n';

  // Print the final form of the list
  std::cout << "print elements:\n";
  for(dlist::list<int>::iterator itr = l.begin(); itr != l.end(); itr++)
    std::cout << *itr << std::endl;
  std::cout << '\n';

  return 0;
}
