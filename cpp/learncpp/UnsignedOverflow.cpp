#include <iostream>

void doSomething(unsigned int x)
{
    // Run some code x times

    std::cout << "x is " << x << '\n';
}

int main()
{
    unsigned short x{ 65535 }; // largest 16-bit unsigned value possible
    std::cout << "x was: " << x << '\n';

    x = 65536; // 65536 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = 65537; // 65537 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';
    
    x = -1; // -1 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';

    x = -2; // -2 is out of our range, so we get modulo wrap-around
    std::cout << "x is now: " << x << '\n';
    
    unsigned int z{ 2 };
	  unsigned int y{ 3 };

	  std::cout << z - y << '\n'; // prints 4294967295 (incorrect!)
	  
	  unsigned int u{ 2 };
  	signed int s{ 3 };
  
  	std::cout << u - s << '\n'; // 2 - 3 = 4294967295
  	
  	signed int v { -1 };
    unsigned int w { 1 };

    if (v < w) // -1 is implicitly converted to 4294967295, and 4294967295 < 1 is false
        std::cout << "-1 is less than 1\n";
    else
        std::cout << "1 is less than -1\n"; // this statement executes
    
    doSomething(-1);

    return 0;
}