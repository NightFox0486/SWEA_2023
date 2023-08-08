#include <cmath>
#include <iostream>
#include <queue>

using namespace std;

int        N;
int        parent[100010];
int        depth[100010];
int        dp[100010][16];
long long  cnt = 0;
queue<int> child[100010];
queue<int> order;

void solve() {
	int front;
	int current;
	order.push(1);
	while (!order.empty())
	{
		front = order.front();
		while (!child[front].empty())
		{
			order.push(child[front].front());
			child[front].pop();
		}
		order.pop();
		if (order.empty())
			break;
		current   = order.front();
		bool flag = false;
		if (depth[current] != depth[front])
		{
			current = parent[current];
			flag    = true;
		}
		int save_current = current;
		int iter         = 0;
		while (current != front)
		{
			if (depth[current] < pow(2, iter))
			{
				iter = 0;
			}
			if (dp[current][iter] != dp[front][iter])
			{
				current = dp[current][iter];
				front   = dp[front][iter];
			}
			else if (iter = 0)
			{
				current = dp[current][0];
				front   = dp[front][0];
			}
			else
			{
				iter = -1;
			}
			iter++;
		}
		if (flag)
			cnt += (2 * (depth[save_current] - depth[current])) + 1;
		else
			cnt += (2 * (depth[save_current] - depth[current]));
	}
}

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		cin >> N;
		int from;
		depth[1] = 0;
		for (int i = 2; i <= N; i++)
		{
			cin >> from;
			parent[i] = from;
			child[from].push(i);
			depth[i] = depth[from] + 1;
			dp[i][0] = from;
			for (int j = 1; j < floor(log2(depth[i])) + 1; j++)
			{
				dp[i][j] = dp[dp[i][j - 1]][j - 1];
			}
			solve();
		}
		cout << "#" << t << " "
		     << cnt << endl;
		cnt = 0;
	}
	return 0;
}