#include <iostream>

using namespace std;

constexpr int MAX_NODE = 10010;

struct Node
{
	int   data;
	Node *parent;
	Node *left;
	Node *right;
};

Node node_pool[MAX_NODE];
bool visited[MAX_NODE];
int  result;

void scan(int A, Node node)
{
	if (node.left != nullptr)
	{
		scan(A, node_pool[node.left->data]);
	}
	if (node.right != nullptr)
	{
		scan(A, node_pool[node.right->data]);
	}
}

void setVisit(Node node)
{
	Node *current = &node;
	while (current->parent != nullptr)
	{
		visited[current->parent->data] = true;
		current                        = current->parent;
	}
}

int find(Node node)
{
	Node *current = &node;
	while (!visited[current->parent->data])
	{
		current = current->parent;
	}
	return current->parent->data;
}

void count(Node node)
{
	result++;
	if (node.left != nullptr)
	{
		count(node_pool[node.left->data]);
	}
	if (node.right != nullptr)
	{
		count(node_pool[node.right->data]);
	}
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int V, E, A, B;
		cin >> V >> E >> A >> B;
		result = 0;
		for (int i = 0; i < MAX_NODE; i++)
		{
			node_pool[i].data   = i;
			node_pool[i].left   = nullptr;
			node_pool[i].right  = nullptr;
			node_pool[i].parent = nullptr;
			visited[i]          = false;
		}
		for (int i = 0; i < E; i++)
		{
			int from, to;
			cin >> from >> to;
			if (node_pool[from].left == nullptr)
			{
				node_pool[from].left = &node_pool[to];
				node_pool[to].parent = &node_pool[from];
			}
			else if (node_pool[from].right == nullptr)
			{
				node_pool[from].right = &node_pool[to];
				node_pool[to].parent  = &node_pool[from];
			}
			else
			{
				cout << "Already has all child" << endl;
			}
		}
		// scan(A, node_pool[1]);
		setVisit(node_pool[A]);
		int ancestor = find(node_pool[B]);
		count(node_pool[ancestor]);

		cout << "#" << t << " " << ancestor << " " << result << endl;
	}
}