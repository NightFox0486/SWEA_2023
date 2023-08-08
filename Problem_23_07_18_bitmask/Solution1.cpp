#include <algorithm>
#include <iostream>

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int  cnt = 0;
		bool check[10];
		std::fill_n(check, 10, false);

		int N;
		std::cin >> N;
		int value = N;
		int i     = 1;
		while (true)
		{
			int num = value;
			while (num)
			{
				int temp = num % 10;
				if (!check[temp])
				{
					check[temp] = true;
					cnt++;
				}
				num /= 10;
			}

			if (cnt == 10)
			{
				break;
			}
			value = N * ++i;
		}
		std::cout << "#" << t << " " << value << std::endl;
	}
	return 0;
}