#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

constexpr size_t MAX_NODE   = 1010;
int              node_count = 0;

struct Node
{
	std::string data;
	Node       *left;
	Node       *right;
};

Node                    nodelist[MAX_NODE];
std::stack<std::string> st;

class Tree
{
private:
	int size;

public:
	Tree(int N)
	{
		for (int i = 0; i < 1010; i++)
		{
			nodelist[i].left  = nullptr;
			nodelist[i].right = nullptr;
		}
		node_count = 0;
		size       = 0;
	}

	void treeInsert(int index, std::string data)
	{
		nodelist[index].data = data;
		size++;
	}

	void treeInsert(int index, std::string data, int left)
	{
		nodelist[index].data = data;
		nodelist[index].left = &nodelist[left];
		size++;
	}

	void treeInsert(int index, std::string data, int left, int right)
	{
		nodelist[index].data  = data;
		nodelist[index].left  = &nodelist[left];
		nodelist[index].right = &nodelist[right];
		size++;
	}

	int getSize()
	{
		return size;
	}
};
int opCheck(std::string data)
{
	if (data == "+" || data == "-" || data == "*" || data == "/")
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int calulate(std::string data1, std::string data2, std::string oper)
{
	double num1 = std::stod(data1);
	double num2 = std::stod(data2);
	double result;
	switch (oper.at(0))
	{
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num2 - num1;
			break;
		case '*':
			result = num2 * num1;
			break;
		case '/':
			result = num2 / num1;
			break;
	}
	return result;
}

void operation()
{
	std::string oper = st.top();
	st.pop();
	std::string data1 = st.top();
	st.pop();
	std::string data2 = st.top();
	st.pop();
	if (!opCheck(data1) && !opCheck(data2) && opCheck(oper))
	{
		int result = calulate(data1, data2, oper);
		st.emplace(std::to_string(result));
	}
	else
	{
		st.emplace(data2);
		st.emplace(data1);
		st.emplace(oper);
	}
}

void solve(Node *node)
{
	if (node == nullptr)
		return;
	solve(node->left);
	solve(node->right);
	st.emplace(node->data);
	if (st.size() > 2)
	{
		operation();
	}
}

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
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1));
			}
			else if (ops.size() == 3)
			{
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1), std::stoi(ops.at(2)));
			}
			else
			{
				tree->treeInsert(std::stoi(ops.at(0)), ops.at(1), std::stoi(ops.at(2)), std::stoi(ops.at(3)));
			}
		}
		solve(&nodelist[1]);
		std::cout << "#" << t << " " << st.top() << std::endl;
		st.pop();
	}
}