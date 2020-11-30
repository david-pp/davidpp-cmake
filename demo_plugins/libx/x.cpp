#include "x.h"
#include <iostream>

#ifdef LIBVERSION_V2

void ShowX(const std::string &title) {
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << " --V2:-- " << title << std::endl;
}

#else
void ShowX(const std::string &title) {
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << " --V1:-- " << title << std::endl;
}
#endif