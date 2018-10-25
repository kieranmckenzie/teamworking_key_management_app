#include "test.h"
#include <string>
#include <iostream>

test::test(){
    std::string str ("ffs test ffs");
    std::string str2 ("test");
    if (str.find(str2) != std::string::npos) {
        std::cout << "found 'test'" << "\n";
    } else {
        std::cout << "didnt find 'test'" << "\n";
    }
}
