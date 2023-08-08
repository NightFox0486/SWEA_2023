#include <iostream>
#include <queue>

using namespace std;

struct cmp {
	bool operator()(int a, int b) {
		return a > b;
	}
};

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		priority_queue<int>                   MaxHeap;
		priority_queue<int, vector<int>, cmp> MinHeap;
		int                                   N, Mid;
		cin >> N >> Mid;
		int result = 0;
		for (int i = 0; i < N; i++) {
			int X, Y;
			cin >> X >> Y;
			if (X < Mid) {
				MaxHeap.emplace(X);
			}
			else {
				MinHeap.emplace(X);
			}
			if (Y < Mid) {
				MaxHeap.emplace(Y);
			}
			else {
				MinHeap.emplace(Y);
			}
			if (MinHeap.size() != MaxHeap.size()) {
				if (MinHeap.size() < MaxHeap.size()) {
					while (MinHeap.size() != MaxHeap.size()) {
						int temp = MaxHeap.top();
						MaxHeap.pop();
						MinHeap.emplace(Mid);
						Mid = temp;
					}
				}
				else {
					while (MinHeap.size() != MaxHeap.size()) {
						int temp = MinHeap.top();
						MinHeap.pop();
						MaxHeap.emplace(Mid);
						Mid = temp;
					}
				}
			}
			// cout << Mid << endl;
			result += Mid % 20171109;
			result %= 20171109;
		}
		cout << "#" << t << " " << result << endl;
	}
	return 0;
}