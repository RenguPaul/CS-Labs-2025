#include "MyVector/MyVector.h"
#include "MySet/MySet.h"


int main() {
    MySet<int>aa{};
    MySet<int>gg{};
    aa.add_element(1);
    aa.add_element(4);
    aa.add_element(5);
    aa.add_element(6);
    gg.add_element(1);
    gg.add_element(2);
    gg.add_element(3);
    gg.add_element(4);
    std::cout << aa -gg << std::endl;
    std::cout << aa * gg << std::endl;
    std::cout << aa + gg << std::endl;
    return 0;

}
