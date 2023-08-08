#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

struct User {
	int uID, height;
	User(){};
	User(int uID, int height) :
	    uID(uID), height(height) {
	}
};

struct cmp {
	bool operator()(User a, User b) {
		if (a.height == b.height)
			return a.uID > b.uID;
		return a.height < b.height;
	}
};

std::priority_queue<User, std::vector<User>, cmp> queue;

void init() {
	for (int i = 0; i < queue.size(); i++) {
		queue.pop();
	}
}

void addUser(int uID, int height) {
	queue.emplace(User(uID, height));
}

int getTop10(int result[10]) {
	int  i = 0;
	User users[10];
	for (; i < 10; i++) {
		if (!queue.empty()) {
			users[i]  = queue.top();
			result[i] = users[i].uID;
			// printf("%d : %d\n", users[i].uID, users[i].height);
			queue.pop();
		}
		else {
			break;
		}
	}
	for (int j = 0; j < i; j++) {
		queue.emplace(users[j]);
	}
	return i;
}

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand() {
	seed = seed * 214013 + 2531011;
	return (unsigned int) (seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen) {
	for (int i = 0; i < inputLen; i++) {
		input[i] = pseudoRand();
	}
}

static int run() {
	int N, userNum, uID = 0;
	int score = 100, result[10], cnt;
	int sum, check;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &userNum);
		makeInput(userNum);
		for (int j = 0; j < userNum; j++) {
			addUser(uID++, input[j]);
		}
		cnt = getTop10(result);

		sum = 0;
		for (int j = 0; j < cnt; j++)
			sum += result[j];
		scanf("%d", &check);
		if (check != sum)
			score = 0;
	}
	return score;
}

int main(void) {
	setbuf(stdout, NULL);
	// freopen("partial_sort_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		printf("#%d %d\n", tc, run());
	}
	return 0;
}