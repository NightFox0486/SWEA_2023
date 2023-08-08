#include <iostream>
#include <queue>

using namespace std;

int parent[50010];

struct Node {
	int from, to, cost;
	Node(int from, int to, int cost) :
	    from(from), to(to), cost(cost) {
	}
	bool operator<(const Node node) const {
		if (cost > node.cost)
			return true;
		else
			return false;
	}
};

int getParent(int x) {
	if (parent[x] == x)
		return x;
	return parent[x] = getParent(parent[x]);
}

void unionParent(int a, int b) {
	a = getParent(a);
	b = getParent(b);
	if (a < b)
		parent[b] = a;
	else
		parent[a] = b;
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		int M;
		int cnt    = 0;
		int result = 0;
		cin >> N;
		cin >> M;
		for (int i = 0; i <= N; i++) {
			parent[i] = i;
		}
		priority_queue<Node> queue;
		for (int i = 0; i < M; i++) {
			int s, e, c;
			cin >> s >> e >> c;
			queue.emplace(Node(s, e, c));
		}
		while (!queue.empty()) {
			Node node = queue.top();
			queue.pop();
			if (getParent(node.from) != getParent(node.to)) {
				result += node.cost;
				// cout << node.from << " : " << node.to << " : " << node.cost << endl;
				unionParent(node.from, node.to);
			}
		}
		cout << "#" << t << " " << result << endl;
	}
	return 0;
}