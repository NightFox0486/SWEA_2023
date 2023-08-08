#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

constexpr size_t MAX_NODE   = 1000;
int              node_count = 0;

struct Node
{
	char  data;
	Node *left;
	Node *right;
};

Node nodelist[MAX_NODE];

class Tree
{
private:
	int size;

public:
	Tree(int N)
	{
		for (int i = 0; i < 101; i++)
		{
			nodelist[i].left  = nullptr;
			nodelist[i].right = nullptr;
		}
		node_count = 0;
		size       = 0;
	}
	void treeInsert(int index, char data)
	{
		nodelist[index].data = data;
		size++;
	}
	void treeInsert(int index, char data, int left)
	{
		nodelist[index].data = data;
		nodelist[index].left = &nodelist[left];
		size++;
	}
	void treeInsert(int index, char data, int left, int right)
	{
		nodelist[index].data  = data;
		nodelist[index].left  = &nodelist[left];
		nodelist[index].right = &nodelist[right];
		size++;
	}
	void inorder(Node *node)
	{
		if (node == nullptr)
			return;
		inorder(node->left);
		std::cout << node->data;
		inorder(node->right);
	}
};

int main()
{
	int T = 10;
	for (int t = 1; t <= T; t++)
	{
		int N;
		std::cin >> N;
		std::cin.ignore();
		Tree *tree = new Tree(N);
		for (int i = 0; i < N; i++)
		{
			std::string temp;
			std::getline(std::cin, temp);
			std::stringstream        ss(temp);
			std::vector<std::string> ops;
			std::string              word;

			while (getline(ss, word, ' '))
			{
				ops.push_back(word);
			}

			if (ops.size() == 2)
			{
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1).at(0));
			}
			else if (ops.size() == 3)
			{
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1).at(0), std::stoi(ops.at(2)));
			}
			else if (ops.size() == 4)
			{
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1).at(0), std::stoi(ops.at(2)), std::stoi(ops.at(3)));
			}
		}
		std::cout << "#" << t << " ";
		tree->inorder(&nodelist[1]);
		std::cout << std::endl;
	}
}