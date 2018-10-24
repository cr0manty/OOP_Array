#include <iostream>
#include "Array.hpp"

int main()
{
	Array<int> arr;
	Array<int> arr1;
	arr.push_back(5);
	arr.push_back(6);
	Array<int>::iterator begin = arr.begin();
	Array<int>::iterator end = arr.end();
	for (auto i : arr)
		std::cout << i;
	std::cout << std::endl;
	for(; begin != end; begin++)
		std::cout << (*begin);


	arr1 = Array<int>(10);
	getchar();
	return 0;
}