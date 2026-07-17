#include <iostream>

int main()
{
    char ch1{ 'a' }; // (preferred)
    std::cout << ch1; // cout prints character 'a'

    char ch2{ 98 }; // code point for 'b' (not preferred)
    std::cout << ch2 << std::endl; // cout prints a character ('b')
    
    std::cout << "Input a keyboard character: ";

    char ch{};
    std::cin >> ch;
    std::cout << "You entered: " << ch << '\n' << std::flush;
    
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)
    

    char ch3{};
    std::cin.get(ch3); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch3 << '\n';

    std::cin.get(ch3); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch3 << '\n';


    return 0;
}