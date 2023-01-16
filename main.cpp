#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <csignal>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

#include <unistd.h>

// Author: Algin Andrey Vladimirovich (Альгин Андрей Владимирович)
// Date: 16.01.2023
// Elapsed time: 8 hours

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
		std::unordered_map<ListNode*, int> map;

		Index(map);

		rewind(file);

		fwrite(&count, sizeof(count), 1, file);

		while(current != nullptr)
		{
			int rand = map[current->rand];
			size_t size = current->data.size();

			fwrite(&rand, sizeof(rand), 1, file);
			fwrite(&size, sizeof(size), 1, file);
			fwrite(current->data.data(), size, 1, file);

			current = current->next;
		}

		fflush(file);
	}

	void Deserialize(FILE* file)
	{
		int nodeCount = 0;

		rewind(file);

		fread(&nodeCount, sizeof(nodeCount), 1, file);

		if(feof(file) != 0)
		{
			return;
		}

		ListNode* nodes[nodeCount];

		for(ListNode* node : nodes)
		{
			int rand = 0;
			size_t size = 0;

			if(node == nullptr)
			{
				node = new ListNode();
			}
			
			fread(&rand, sizeof(rand), 1, file);
			fread(&size, sizeof(size), 1, file);

			char buffer[size];

			fread(buffer, size, 1, file);

			if(rand != -1)
			{
				if(nodes[rand] == nullptr)
				{
					nodes[rand] = new ListNode();
				}

				node->rand = nodes[rand];
			}

			node->data = buffer;

			PushBack(node);
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

	void Index(std::unordered_map<ListNode*, int>& map)
	{
		ListNode* current = head;
		int counter = 0;

		map.reserve(count + 1);
		map[nullptr] = -1;

		while(current != nullptr)
		{
			map[current] = counter;

			counter++;
			current = current->next;
		}
	}

	ListNode& operator[](size_t i)
	{
		ListNode* current = head;
		size_t counter = 0;

		while(current != nullptr)
		{
			if(i == counter)
			{
				return *current;
			}

			counter++;
			current = current->next;
		}

		raise(SIGSEGV);

		return *current;
	}

private:
	ListNode* head = nullptr;
	ListNode* tail = nullptr;
	int count = 0;
};

//=================================================================

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

	ListNode* node1 = new ListNode{nullptr, nullptr, nullptr, "ABCDE"};
	ListNode* node2 = new ListNode{nullptr, nullptr, nullptr, "FGH"};
	ListNode* node3 = new ListNode{nullptr, nullptr, nullptr, "IJKLMNOPQRSTUVWXYZ"};

	node1->rand = node3;

	list1.PushBack(node1);
	list1.PushBack(node2);
	list1.PushBack(node3);

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

	std::cout << "task_3_list1.bin task_3_list2.bin" << std::endl;
	std::cout << "list2[0].data " << list2[0].data << std::endl;
	std::cout << "list2[0].rand->data " << list2[0].rand->data << std::endl;

	return 0;
}
