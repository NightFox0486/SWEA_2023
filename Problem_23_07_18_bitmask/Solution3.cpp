#include <iostream>
#include <string>

int main()
{
	int T;
	std::cin >> T;
	for (int t = 1; t <= T; t++)
	{
		std::string input;
		std::cin >> input;
		int visited[input.length()][16];
		for (int i = 0; i < input.length(); i++)
		{
			std::fill_n(visited[i], 16, 0);
		}
		int result = 0;
		for (int i = 0; i < input.length(); i++)
		{
			int cheif = 1;
			for (int j = 0; j < input.at(i) - 'A'; j++)
			{
				cheif <<= 1;
			}
			if (i == 0)
			{
				for (int j = 1; j < 16; j++)
				{
					if ((cheif & j) != 0 && (j & 1) != 0)
					{
						visited[0][j] = 1;
					}
				}
			}
			else
			{
				for (int j = 1; j < 16; j++)
				{
					if (visited[i - 1][j])
					{
						for (int k = 1; k < 16; k++)
						{
							if ((cheif & k) != 0 && (k & j) != 0)
							{
								visited[i][k] = (visited[i - 1][j] + visited[i][k]) % 1000000007;
							}
						}
					}
				}
			}
		}
		for (int j = 1; j < 16; j++)
		{
			result = (result + visited[input.length() - 1][j]) % 1000000007;
		}

		std::cout << "#" << t << " " << result << std::endl;
	}

	return 0;
}