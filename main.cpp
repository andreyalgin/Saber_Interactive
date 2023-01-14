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

void RemoveDups(char *str)
{
	uint32_t cursor1 = 0;
	uint32_t cursor2 = 0;

	while((str[cursor1] != '\0') && (str[cursor1] != str[++cursor1]))
	{

	}

	cursor2 = cursor1 - 1;

	while(str[cursor1] != '\0')
	{
		cursor1++;

		if(str[cursor1] != str[cursor2])
		{
			cursor2++;
			
			str[cursor2] = str[cursor1];
		}
	}
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

	std::cout << "Task 2" << std::endl;

	char test[] = "";
	char data[] = "A B C C B A AAA  BB   CCC  AA CCCC  C B A";
	
	RemoveDups(test);
	RemoveDups(data);

	std::cout << data << std::endl;

	return 0;
}
