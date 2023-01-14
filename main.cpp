#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

void PrintBitstring(int input)
{
	size_t counter = sizeof(int)*8;
	char output[counter + 1];
	unsigned int value = static_cast<unsigned int>(input);

	output[counter] = '\0';

	while(counter--)
	{
		output[counter] = '0' + (value&1);

		value >>= 1;
	}

	std::cout << input << ":	" << output << std::endl;
}

int main(int argc, const char* argv[])
{
	std::cout << "Task 1" << std::endl;
	std::cout << "sizeof(int) " << sizeof(int)*8 << "-bits" << std::endl;

	PrintBitstring(0);
	PrintBitstring(1);
	PrintBitstring(-1);
	PrintBitstring(-23357);
	PrintBitstring(23357);
	PrintBitstring(-23358);
	PrintBitstring(23358);


	return 0;
}
