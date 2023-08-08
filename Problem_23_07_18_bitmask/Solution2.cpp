#include <iostream>

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N, M;
		std::cin >> N >> M;
		int source = 1;
		for (int i = 0; i < N - 1; i++)
		{
			source <<= 1;
			source++;
		}

		if ((source & M) == source)
		{
			std::cout << "#" << t << " "
			          << "ON" << std::endl;
		}
		else
		{
			std::cout << "#" << t << " "
			          << "OFF" << std::endl;
		}
	}

	return 0;
}