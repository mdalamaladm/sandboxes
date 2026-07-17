#include <iostream>

// returns true if x and y are equal, false otherwise
bool isEqual(int x, int y)
{
    return x == y; // operator== returns true if x equals y, and false otherwise
}

int main()
{
    std::cout << true << '\n'; // true evaluates to 1
    std::cout << !true << '\n'; // !true evaluates to 0

    bool b {false};
    
    std::cout << std::boolalpha; // print bools as true or false

    std::cout << b << '\n'; // b is false, which evaluates to 0
    std::cout << !b << '\n'; // !b is true, which evaluates to 1
    
    std::cout << std::noboolalpha;
    
    std::cout << b << '\n'; // b is false, which evaluates to 0
    std::cout << !b << '\n'; // !b is true, which evaluates to 1
    
    bool bFalse { 0 }; // okay: initialized to false
  	bool bTrue  { 1 }; // okay: initialized to true
  	// bool bNo    { 2 }; // error: narrowing conversions disallowed
  
  	std::cout << bFalse << bTrue
  	 //  << bNo
  	  << '\n';
  	  
  	std::cout << std::boolalpha; // print bools as true or false

  	bool b1 = 4 ; // copy initialization allows implicit conversion from int to bool
  	std::cout << b1 << '\n';
  
  	bool b2 = 0 ; // copy initialization allows implicit conversion from int to bool
  	std::cout << b2 << '\n';
  	
    std::cout << std::noboolalpha;
  	
  	bool b3{}; // default initialize to false
  	std::cout << "Enter a boolean value: ";
  	std::cin >> b3;
  	std::cout << "You entered: " << b3 << '\n';
  	
  	std::cout << "Enter a boolean value: ";

  	// Allow the user to input 'true' or 'false' for boolean values
  	// This is case-sensitive, so True or TRUE will not work
  	std::cin >> std::boolalpha;
  	std::cin >> b3;
  
  	// Let's also output bool values as `true` or `false`
  	std::cout << std::boolalpha;
  	std::cout << "You entered: " << b3 << '\n';
  	
  	std::cout << "Enter an integer: ";
    int x1{};
    std::cin >> x1;

    std::cout << "Enter another integer: ";
    int y1{};
    std::cin >> y1;

    std::cout << std::boolalpha; // print bools as true or false

    std::cout << x1 << " and " << y1 << " are equal? ";
    std::cout << isEqual(x1, y1) << '\n'; // will return true or false
    
    return 0;
}