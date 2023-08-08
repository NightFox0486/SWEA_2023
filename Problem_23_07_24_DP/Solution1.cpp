#include <iostream>
#include <vector>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		string s1, s2;
		cin >> s1 >> s2;
		// int map[s1.size() + 1][s2.size() + 1];
		// fill_n(&map[0][0], (s1.size() + 1) * (s2.size() + 1), 0);
		vector<vector<int>> map(s1.size() + 1, vector<int>(s2.size() + 1, 0));
		int                 result = 0;

		for (int i = 1; i <= s1.size(); i++) {
			for (int j = 1; j <= s2.size(); j++) {
				if (s1[i - 1] == s2[j - 1]) {
					map[i][j] = map[i - 1][j - 1] + 1;
				}
				else {
					map[i][j] = max(map[i - 1][j], map[i][j - 1]);
				}
			}
		}
		cout << "#" << t << " "
		     << map[s1.size()][s2.size()] << endl;
	}
	return 0;
}