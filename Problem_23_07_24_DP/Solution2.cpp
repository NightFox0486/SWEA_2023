#include <iostream>

using namespace std;

int dp[101][1001];
int V[101];
int C[101];

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int N, K;
		cin >> N >> K;
		for (int i = 1; i <= N; i++) {
			cin >> V[i] >> C[i];
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= K; j++) {
				if (j - V[i] >= 0) {
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - V[i]] + C[i]);
				}
				else {
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		cout << "#" << t << " " << dp[N][K] << endl;
	}
	return 0;
}

// 선택하는 경우 안하는경우 둘 중 큰 값으로 저장