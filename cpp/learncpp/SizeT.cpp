#include <cstddef>  // for std::size_t
#include <iostream>

int main()
{
    int x { 5 };
    std::size_t s { sizeof(x) }; // sizeof returns a value of type std::size_t, so that should be the type of s
    std::cout << s << '\n';
    
    std::cout << sizeof(std::size_t) << '\n';

    return 0;
}