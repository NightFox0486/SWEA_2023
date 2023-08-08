#include <iostream>
#include <queue>

using namespace std;

struct Node {
	int remain;
	int cnt;
	Node(int remain, int cnt) :
	    remain(remain), cnt(cnt) {
	}
};

struct cmp {
	bool operator()(Node a, Node b) {
		return a.cnt > b.cnt;
	}
};

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		cin >> N;
		priority_queue<Node, vector<Node>, cmp> queue;
		int arr[N];
		for (int i = 0; i < N; i++) {
			int input;
			cin >> input;
			arr[i] = input;
		}
		int K;
		cin >> K;
		int cnt = K;
		queue.emplace(Node(K, 0));
		while (!queue.empty()) {
			Node current = queue.top();
			queue.pop();
			if (current.remain == 0) {
				cnt = current.cnt;
				break;
			}
			queue.emplace(Node(0, current.remain + current.cnt));
			for (int i = 0; i < N; i++) {
				queue.emplace(Node((int) (current.remain / arr[i]), current.cnt + current.remain % arr[i]));
			}
		}
		cout << "#" << t << " " << cnt << endl;
	}
	return 0;
}