#include <cstring>
#include <iostream>

using namespace std;

size_t djb2(const char *str) {
	size_t hash = 5381;

	for (; *str; ++str) {
		hash = ((hash << 5) + hash) + *str;
	}
	return hash;
}

constexpr size_t MAX_N = 100010;
constexpr size_t MAX_LEN = 60;

struct Node {
	char str[MAX_LEN + 1];
	int data;
	Node *next;
};

int node_count = 0;
Node nodes[MAX_N];

Node *new_node(const char str[MAX_LEN + 1], int data) {
	strcpy(nodes[node_count].str, str);
	nodes[node_count].data = data;
	nodes[node_count].next = nullptr;

	return &nodes[node_count++];
}

class HashMap {
	static constexpr size_t TABLE_SIZE = 1 << 12;
	static constexpr size_t DIV = TABLE_SIZE - 1;

	Node hash_table[TABLE_SIZE];

public:
	HashMap() = default;

	void init() {
		memset(hash_table, 0, sizeof hash_table);
		node_count = 0;
	}

	void insert(const char str[MAX_LEN + 1], int data) {
		Node *const prev_node = get_prev_node(str);
		if (prev_node->next == nullptr) {
			prev_node->next = new_node(str, data);
		}
		else {
			prev_node->next->data = data;
		}
	}

	void remove(const char str[MAX_LEN + 1]) {
		Node *const prev_node = get_prev_node(str);
		if (prev_node->next != nullptr) {
			prev_node->next = prev_node->next->next;
		}
	}
	Node *get(const char str[MAX_LEN + 1]) {
		return get_prev_node(str)->next;
	}

private:
	Node *get_prev_node(const char str[MAX_LEN + 1]) {
		Node *prev_ptr = &hash_table[djb2(str) & DIV];
		while (prev_ptr->next != nullptr && strcmp(prev_ptr->next->str, str) != 0) {
			prev_ptr = prev_ptr->next;
		}
		return prev_ptr;
	}
};

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N, M, cnt = 0;
		cin >> N >> M;
		HashMap map{};
		map.init();
		for (int i = 0; i < N; i++) {
			string temp;
			cin >> temp;
			map.insert(temp.c_str(), 0);
		}
		for (int i = 0; i < M; i++) {
			string temp;
			cin >> temp;
			Node *ptr;
			ptr = map.get(temp.c_str());
			if (ptr != nullptr && ptr->data == 0) {
				cnt++;
			}
		}
		cout << "#" << t << " " << cnt << endl;
	}
	return 0;
}