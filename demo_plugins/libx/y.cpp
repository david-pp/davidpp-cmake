#include "y.h"
#include <iostream>

#ifdef LIBVERSION_V2

void DontShowX(const std::string &title) {
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << " --V2:-- " << title << std::endl;
}
#else

void DontShowX(const std::string &title) {
    std::cout << __FILE__ << ":" << __PRETTY_FUNCTION__ << " --V1:-- " << title << std::endl;
}
#endif