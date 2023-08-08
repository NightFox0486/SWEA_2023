#include <iostream>

struct Node
{
	int   data;
	Node *next;
	Node *prev;
};

constexpr size_t MAX_NODE = 10000;

int  node_count = 0;
Node node_pool[MAX_NODE];

Node *newNode(int data)
{
	node_pool[node_count].data = data;
	node_pool[node_count].next = nullptr;
	node_pool[node_count].prev = nullptr;

	return &node_pool[node_count++];
}

class LinkedList
{
private:
	Node *head;
	Node *tail;

public:
	LinkedList()
	{
		node_count = 0;
		head       = newNode(-1);
		tail       = newNode(-1);
		head->next = tail;
		tail->prev = head;
	}

	void addLast(int data)
	{
		Node *node       = newNode(data);
		node->prev       = tail->prev;
		node->next       = tail;
		tail->prev->next = node;
		tail->prev       = node;
	}

	void addIndex(int index, int num)
	{
		Node *current = head;
		Node *node    = newNode(num);
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		node->prev          = current;
		node->next          = current->next;
		current->next->prev = node;
		current->next       = node;
	}

	void removeIndex(int index)
	{
		Node *current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		current->next->next->prev = current;
		current->next             = current->next->next;
	}

	void changeIndex(int index, int data)
	{
		Node *current = head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		current->next->data = data;
	}

	int getIndex(int index)
	{
		Node *current = head;
		for (int i = 0; i < index; i++)
		{
			if (current->next->next == nullptr)
			{
				return -1;
			}
			current = current->next;
		}
		return current->next->data;
	}

	void print()
	{
		Node *current = head;
		while (current->next->next != nullptr)
		{
			current = current->next;
			std::cout << current->data << "->";
		}
	}
};

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N, M, L;
		std::cin >> N >> M >> L;
		LinkedList *list = new LinkedList();
		int         input;
		for (int i = 0; i < N; i++)
		{
			std::cin >> input;
			list->addLast(input);
		}
		// list->print();
		for (int i = 0; i < M; i++)
		{
			char opcode;
			std::cin >> opcode;
			int index, num;
			switch (opcode)
			{
				case 'I':
					std::cin >> index >> num;
					list->addIndex(index, num);
					break;
				case 'D':
					std::cin >> index;
					list->removeIndex(index);
					break;
				case 'C':
					std::cin >> index >> num;
					list->changeIndex(index, num);
					break;
			}
			// list->print();
		}
		std::cout << "#" << t << " " << list->getIndex(L) << std::endl;
		delete list;
	}
	return 0;
}