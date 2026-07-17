#include <iostream>

#define PRINT_BOB

int main()
{
#if 1
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif

#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif
#endif

#ifndef PRINT_JOE
  std::cout << "Joe is not defined\n";
#endif

    return 0;
}