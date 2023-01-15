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

//=========================== Task 1 =======================================

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

//=========================== Task 2 =======================================

void RemoveDups(char *str)
{
	char *cursor1 = str;
	char *cursor2 = str;

	while((*cursor1 != '\0') && (*cursor1 != *(++cursor1)))
	{
	}

	cursor2 = cursor1 - 1;

	while(*cursor1 != '\0')
	{
		cursor1++;

		if(*cursor1 != *cursor2)
		{
			cursor2++;
			
			*cursor2 = *cursor1;
		}
	}
}

//=========================== Task 3 =======================================

struct ListNode
{
	ListNode* prev;
	ListNode* next;
	ListNode* rand;
	std::string data;
};

class List
{
public:
	void Serialize(FILE* file)
	{
		ListNode* current = head;

		rewind(file);

		while(current != nullptr)
		{
			size_t size = current->data.size();

			fwrite(&size, sizeof(size), 1, file);
			fwrite(current->data.data(), size, 1, file);

			current = current->next;
		}

		fflush(file);
	}

	void Deserialize(FILE* file)
	{
		rewind(file);

		while(feof(file) == 0)
		{
			size_t size = 0;

			fread(&size, sizeof(size), 1, file);

			if(feof(file) != 0)
			{
				break;
			}

			char buffer[size];

			fread(buffer, size, 1, file);

			PushBack(new ListNode{nullptr, nullptr, nullptr, buffer});
		}
	}

	void PushBack(ListNode* node)
	{
		if(tail != nullptr)
		{
			node->prev = tail;
			tail->next = node;
		}

		if(head == nullptr)
		{
			head = node;
		}

		tail = node;
		count++;
	}

private:
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	int count = 0;
};


int main(int argc, const char* argv[])
{
	// Task 1
	std::cout << "Task 1" << std::endl;
	std::cout << "sizeof(int) " << sizeof(int)*8 << "-bits" << std::endl;

	PrintBitstring(0);
	PrintBitstring(1);
	PrintBitstring(-1);
	PrintBitstring(-23357);
	PrintBitstring(23357);
	PrintBitstring(-23358);
	PrintBitstring(23358);

	// Task 2
	std::cout << "Task 2" << std::endl;

	char test[] = "";
	char data[] = "A B C C B A AAA  BB   CCC  AA CCCC  C B A";
	
	RemoveDups(test);
	RemoveDups(data);

	std::cout << data << std::endl;

	// Task 3
	std::cout << "Task 3" << std::endl;

	List list1;
	List list2;
	FILE *fp;

	fp = fopen("task_3_list1.bin", "wb");
	if(fp == NULL)
	{
		std::cout << "Can't open file" << std::endl;

		exit(EXIT_FAILURE);
	}

	list1.PushBack(new ListNode{nullptr, nullptr, nullptr, "ABCDE"});
	list1.PushBack(new ListNode{nullptr, nullptr, nullptr, "FGH"});
	list1.PushBack(new ListNode{nullptr, nullptr, nullptr, "IJKLMNOPQRSTUVWXYZ"});

	list1.Serialize(fp);

	fclose(fp);

	fp = fopen("task_3_list1.bin", "rb");
	if(fp == NULL)
	{
		std::cout << "Can't open file" << std::endl;

		exit(EXIT_FAILURE);
	}

	list2.Deserialize(fp);

	fclose(fp);

	fp = fopen("task_3_list2.bin", "wb");
	if(fp == NULL)
	{
		std::cout << "Can't open file" << std::endl;

		exit(EXIT_FAILURE);
	}

	list2.Serialize(fp);

	fclose(fp);

	std::cout << "task_3_list1.bin" << " " << "task_3_list2.bin" << std::endl;

	return 0;
}
