#include <iostream>

 class A {
  public:
      void f(int) { std::cout << "A\n"; }
  };
  class B : public A {
  public:
      using A::f; // Делает A::f видимым в B
      void f(double) { std::cout << "B\n"; }
  };
  int main() {
      B b;
      b.f(1.); // Вызов A::f(int)
  }
