#include <iostream>

int add(int x, int y)
{
	return x + y;
}

void testadd()
{
	std::cout << "This function should print:\n2 0 0 -2\n";
	std::cout << add(1, 1) << ' ';
	std::cout << add(-1, 1) << ' ';
	std::cout << add(1, -1) << ' ';
	std::cout << add(-1, -1) << " \n";
}

int main()
{
	testadd();

	return 0;
}