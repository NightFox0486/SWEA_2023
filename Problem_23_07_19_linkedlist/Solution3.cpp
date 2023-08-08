#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

struct Node
{
	int   data;
	Node *next;
};

Node  node[MAX_NODE];
int   nodeCnt;
Node *head;
int   listSize;

Node *getNode(int data)
{
	node[nodeCnt].data = data;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init()
{
	head     = nullptr;
	nodeCnt  = 0;
	listSize = 0;
}

void addNode2Head(int data)
{
	Node *node = getNode(data);
	if (listSize == 0)
	{
		head = node;
	}
	else
	{
		node->next = head;
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
	}
	else
	{
		Node *current = head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = node;
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
		node->next    = current->next;
		current->next = node;
		listSize++;
	}
}

void removeNode(int data)
{
	Node *current = head;
	if (listSize > 0)
	{
		if (current->data == data)
		{
			head = current->next;
			listSize--;
			return;
		}
		while (current->next != nullptr)
		{
			if (current->next->data == data)
			{
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

enum
{
	ADD_HEAD = 1,
	ADD_TAIL,
	ADD_NUM,
	REMOVE,
	PRINT,
	END = 99
};

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern void removeNode(int data);
extern int  getList(int output[MAX_NODE]);

static void run()
{
	while (1)
	{
		int cmd, data, num, cnt, i;
		int output[MAX_NODE] = {0};

		scanf("%d", &cmd);
		switch (cmd)
		{
			case ADD_HEAD:
				scanf("%d", &data);
				addNode2Head(data);
				break;
			case ADD_TAIL:
				scanf("%d", &data);
				addNode2Tail(data);
				break;
			case ADD_NUM:
				scanf("%d %d", &data, &num);
				addNode2Num(data, num);
				break;
			case REMOVE:
				scanf("%d", &data);
				removeNode(data);
				break;
			case PRINT:
				cnt = getList(output);
				i   = 0;
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
	// freopen("sll_input.txt", "r", stdin);

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