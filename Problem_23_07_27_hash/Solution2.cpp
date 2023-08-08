#include <iostream>
#include <unordered_map>

using namespace std;

int main() {
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++) {
		int result = 0;
		string source, sub;
		cin >> source;
		cin >> sub;
		int table[sub.length() + 1] = {
		    0,
		};
		for (int k = 1; k < sub.length(); k++) {
			int j = table[k - 1];
			while (j > 0) {
				if (sub[k] == sub[j]) {
					break;
				}
				j = table[j - 1];
			}
			if (sub[k] == sub[j]) {
				table[k] = j + 1;
			}
			else {
				table[k] = 0;
			}
		}
		int idx = 0, cnt = 0;
		while (source[idx]) {
			if (source[idx] == sub[cnt]) {
				if (!sub[cnt + 1]) {
					result++;
					cnt = table[cnt];
				}
				else {
					cnt++;
				}
				idx++;
			}
			else if (cnt > 0) {
				cnt = table[cnt - 1];
			}
			else {
				idx++;
			}
		}
		cout << "#" << t << " " << result << endl;
	}
	return 0;
}