#include "task1.h"
#include "task2.h"
#include <iostream>
#include <ostream>
#include <vector>

class A {
public:
  A(int aValue) { this->a = aValue; }
  int getA() const { return this->a; }

private:
  int a;
};

int main() {
  std::cout << task::say_hello("world") << std::endl;
  //std::vector<int, int> ggg;
  const int x = 2;
  const int y = 3;
  std::cout << x << " + " << y << " = " << task::plus(x, y) << std::endl;

  std::cout << "Class usage example" << std::endl;
  auto a = new A(742);
  std::cout << a->getA() << std::endl;
  return 0;
}