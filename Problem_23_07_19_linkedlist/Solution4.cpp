#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

struct Node
{
	int   data;
	Node *prev;
	Node *next;
};

Node  node[MAX_NODE];
int   nodeCnt;
Node *head;
Node *tail;
int   listSize;

Node *getNode(int data)
{
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	nodeCnt  = 0;
	head     = nullptr;
	listSize = 0;
}

void addNode2Head(int data)
{
	Node *node = getNode(data);
	if (listSize == 0)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->next = head;
		head->prev = node;
		head       = node;
	}
	listSize++;
}

void addNode2Tail(int data)
{
	Node *node = getNode(data);
	if (listSize == 0)
	{
		head = node;
		tail = node;
	}
	else
	{
		node->prev = tail;
		tail->next = node;
		tail       = node;
	}
	listSize++;
}

void addNode2Num(int data, int num)
{
	Node *node = getNode(data);
	if (num == 1)
	{
		addNode2Head(data);
	}
	else
	{
		Node *current = head;
		for (int i = 2; i < num; i++)
		{
			current = current->next;
		}
		node->prev = current;
		node->next = current->next;
		if (current->next != nullptr)
		{
			current->next->prev = node;
		}
		else
		{
			tail = node;
		}
		current->next = node;
		listSize++;
	}
}

int findNode(int data)
{
	int   index   = 1;
	Node *current = head;
	do
	{
		if (current->data == data)
		{
			return index;
		}
		current = current->next;
		index++;
	} while (current != nullptr);
	return 0;
}

void removeNode(int data)
{
	Node *current = head;
	if (listSize > 0)
	{
		if (current->data == data)
		{
			current->next->prev = nullptr;
			head                = current->next;
			listSize--;
			return;
		}
		while (current->next != nullptr)
		{
			if (current->next->data == data)
			{
				if (current->next->next != nullptr)
				{
					current->next->next->prev = current;
				}
				else
				{
					tail = current;
				}
				current->next = current->next->next;
				listSize--;
				if (listSize == 0)
				{
					head = nullptr;
				}
				break;
			}
			current = current->next;
		}
	}
}

int getList(int output[MAX_NODE])
{
	int   i       = 0;
	Node *current = head;
	do
	{
		output[i++] = current->data;
		current     = current->next;
	} while (current != nullptr);
	return i;
}

int getReversedList(int output[MAX_NODE])
{
	int   i       = 0;
	Node *current = tail;
	do
	{
		output[i++] = current->data;
		current     = current->prev;
	} while (current != nullptr);
	return i;
}

enum
{
	ADD_HEAD = 1,
	ADD_TAIL,
	ADD_NUM,
	FIND,
	REMOVE,
	PRINT,
	PRINT_REVERSE,
	END = 99
};

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int  findNode(int data);
extern void removeNode(int data);
extern int  getList(int output[MAX_NODE]);
extern int  getReversedList(int output[MAX_NODE]);

static void run()
{
	while (1)
	{
		int cmd, data, num, cnt, i = 0;
		int output[MAX_NODE] = {0};

		scanf("%d", &cmd);
		switch (cmd)
		{
			case ADD_HEAD:        // 1
				scanf("%d", &data);
				addNode2Head(data);
				break;
			case ADD_TAIL:        // 2
				scanf("%d", &data);
				addNode2Tail(data);
				break;
			case ADD_NUM:        // 3
				scanf("%d %d", &data, &num);
				addNode2Num(data, num);
				break;
			case FIND:        // 4
				scanf("%d", &data);
				num = findNode(data);
				printf("%d\n", num);
				break;
			case REMOVE:        // 5
				scanf("%d", &data);
				removeNode(data);
				break;
			case PRINT:        // 6
				cnt = getList(output);
				while (cnt--)
					printf("%d ", output[i++]);
				printf("\n");
				break;
			case PRINT_REVERSE:        // 7
				cnt = getReversedList(output);
				while (cnt--)
					printf("%d ", output[i++]);
				printf("\n");
				break;
			case END:
				return;
		}
	}
}

int main(void)
{
	// setbuf(stdout, NULL);
	// freopen("dll_input.txt", "r", stdin);

	int T;
	scanf("%d", &T);
	for (int t = 1; t <= T; t++)
	{
		printf("#%d\n", t);
		init();
		run();
		printf("\n");
	}

	return 0;
}