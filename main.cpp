#include <iostream>

#include "cadextest.h"

int main() {
    CadexTest cadexTest;

//    std::cout << "Random " << cadexTest.GetRandomParam() << std::endl;
//    std::cout << "size " << sizeof( 1.0) << std::endl;
    cadexTest.Run();
    return 0;
}
