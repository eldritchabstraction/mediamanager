#ifndef ERROR_H
#define ERROR_H
#include <string>
#include <iostream>

inline void error_print(std::string output)
{
    std::cout << "ERROR: " << output << std::endl;
    exit(1);
}
#endif
