#ifndef DEBUG_H
#define DEBUG_H
#include <iostream>
#include <string>

#define DEBUG 0

#ifdef DEBUG
#define debug_print(x) std::cout << "DEBUG: " << x << std::endl
#define debug_print_no_endl(x) std::cout << "DEBUG: " << x
#else
#define debug_print(x) while(0)
#define debug_print_no_endl(x) while(0)
#endif

#endif
