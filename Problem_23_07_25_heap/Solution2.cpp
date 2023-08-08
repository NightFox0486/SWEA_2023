#include <iostream>
#include <queue>

int main() {
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; t++) {
		int N;
		std::cin >> N;
		std::string              result;
		std::priority_queue<int> PQ;
		result += "#";
		result += std::to_string(t);
		for (int i = 0; i < N; i++) {
			int oper;
			std::cin >> oper;
			if (oper == 1) {
				int x;
				std::cin >> x;
				PQ.emplace(x);
			}
			else {
				if (!PQ.empty()) {
					result += " ";
					result += std::to_string(PQ.top());
					PQ.pop();
				}
				else {
					result += " ";
					result += std::to_string(-1);
				}
			}
		}
		std::cout << result << std::endl;
	}
	return 0;
}