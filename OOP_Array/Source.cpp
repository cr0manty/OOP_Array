#include <iostream>
#include "Array.hpp"

int main()
{
	Array<int> arr;
	Array<int> arr1;
	arr.push_back(5);
	arr.push_back(6);
	Array<int>::iterator it;
	it = arr.end();
	arr.capacity();
	for(;it != arr.begin(); it--)
		std::cout << (*it);


	arr1 = Array<int>(10);
	getchar();
	return 0;
}