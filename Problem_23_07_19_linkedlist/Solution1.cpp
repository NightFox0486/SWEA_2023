#include <iostream>

struct Node
{
	int   data;
	Node *next;
	Node *previous;
};

constexpr size_t MAX_NODE = 10000;

int  node_count = 0;
Node node_pool[MAX_NODE];

Node *new_node(int data)
{
	node_pool[node_count].data     = data;
	node_pool[node_count].next     = nullptr;
	node_pool[node_count].previous = nullptr;

	return &node_pool[node_count++];
}

class LinkedList
{
private:
	Node *head;
	Node *tail;
	int   size;

public:
	LinkedList()
	{
		head = nullptr;
		tail = nullptr;
		size = 0;
	}
	void add_first(int data)
	{
		Node *node = new_node(data);
		if (size == 0)
		{
			head = node;
			tail = node;
		}
		else
		{
			node->next     = head;
			head->previous = node;
			head           = node;
		}
		size++;
	}
	void add_last(int data)
	{
		Node *node = new_node(data);
		if (size == 0)
		{
			head = node;
			tail = node;
		}
		else
		{
			tail->next     = node;
			node->previous = tail;
			tail           = node;
		}
		size++;
	}
	void add_index(int index, int data)
	{
		Node *node = new_node(data);
		if (index == 0)
		{
			add_first(data);
		}
		else if (index == size - 1)
		{
			add_last(data);
		}
		else
		{
			if (index < size)
			{
				Node *current = head;
				for (int i = 0; i < index; i++)
				{
					current = current->next;
				}
				current->previous->next = node;
				node->previous          = current->previous;
				current->previous       = node;
				node->next              = current;
				size++;
			}
			else
			{
				throw std::out_of_range("Index out of range");
			}
		}
	}
	void remove_first()
	{
		if (size == 1)
		{
			head = nullptr;
			tail = nullptr;
			size--;
		}
		else if (size > 1)
		{
			head->next->previous = nullptr;
			head                 = head->next;
			size--;
		}
		else
		{
			throw std::out_of_range("list is empty");
		}
	}
	void remove_last()
	{
		if (size == 1)
		{
			head = nullptr;
			tail = nullptr;
			size--;
		}
		else if (size > 1)
		{
			tail->previous->next = nullptr;
			tail                 = tail->previous;
			size--;
		}
		else
		{
			throw std::out_of_range("list is empty");
		}
	}
	void remove_index(int index)
	{
		if (index == 0)
		{
			remove_first();
		}
		else if (index == size - 1)
		{
			remove_last();
		}
		else
		{
			if (index < size)
			{
				Node *current = head;
				for (int i = 0; i < index; i++)
				{
					current = current->next;
				}
				current->previous->next = current->next;
				current->next->previous = current->previous;
				size--;
			}
			else
			{
				throw std::out_of_range("Index out of range");
			}
		}
	}
	void print_list()
	{
		Node *current = head;
		if (size > 9)
		{
			for (int i = 0; i < 9; i++)
			{
				std::cout << current->data << " ";
				current = current->next;
			}
			std::cout << current->data << std::endl;
		}
		else
		{
			while (current != nullptr)
			{
				std::cout << current->data;
				if (current->next != nullptr)
				{
					std::cout << " ";
				}
				else
				{
					std::cout << std::endl;
				}
				current = current->next;
			}
		}
	}
};

int main()
{
	int T = 10;
	for (int t = 1; t <= T; t++)
	{
		int N;
		std::cin >> N;
		LinkedList list = LinkedList();
		node_count      = 0;
		int temp;
		for (int i = 0; i < N; i++)
		{
			std::cin >> temp;
			list.add_last(temp);
		}
		int M;
		std::cin >> M;
		for (int i = 0; i < M; i++)
		{
			char opcode;
			std::cin >> opcode;
			int x, y, s;
			switch (opcode)
			{
				case 'I':
					std::cin >> x >> y;
					for (int j = 0; j < y; j++)
					{
						std::cin >> s;
						list.add_index(x + j, s);
					}
					break;
				case 'D':
					std::cin >> x >> y;
					for (int j = 0; j < y; j++)
					{
						list.remove_index(x);
					}
					break;
				case 'A':
					std::cin >> y;
					for (int j = 0; j < y; j++)
					{
						std::cin >> s;
						list.add_last(s);
					}
					break;
			}
			// list.print_list();
		}

		std::cout << "#" << t << " ";
		list.print_list();
	}
	return 0;
}