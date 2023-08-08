#include <iostream>

using namespace std;

char **map;

int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};

int scan(char **map, int N, int x, int y)
{
	int cnt = 0;
	for (int i = 0; i < 8; i++)
	{
		int sx = x + dy[i];
		int sy = y + dx[i];
		if (sx < 0 || sx >= N || sy < 0 || sy >= N)
			continue;
		if (map[sx][sy] == '*')
			cnt++;
	}
	if (cnt == 0)
		return 0;
	else
		return cnt;
}

void check(char **map, int N, int x, int y)
{
	map[x][y] = '0';
	for (int i = 0; i < 8; i++)
	{
		int sx = x + dy[i];
		int sy = y + dx[i];
		if (sx < 0 || sx >= N || sy < 0 || sy >= N ||
		    (map[sx][sy] != '*' && map[sx][sy] != '.'))
			continue;
		int temp = scan(map, N, sx, sy);
		if (!temp)
		{
			check(map, N, sx, sy);
		}
		else
		{
			map[sx][sy] = '0' + temp;
		}
	}
}

void print(char **map, int N)
{
	printf("////////////////////////////////\n");
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%c", map[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	int T;
	cin >> T;
	for (int t = 1; t <= T; t++)
	{
		int N;
		int result = 0;
		cin >> N;
		map = new char *[N];
		for (int i = 0; i < N; i++)
		{
			map[i] = new char[N];
			for (int j = 0; j < N; j++)
			{
				cin >> map[i][j];
			}
		}
		///////////////////////////////////////////
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == '.')
				{
					if (!scan(map, N, i, j))
					{
						check(map, N, i, j);
						// print(map, N);
						result++;
					}
				}
			}
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (map[i][j] == '.')
					result++;
			}
		}
		///////////////////////////////////////////
		for (int i = 0; i < N; i++)
		{
			delete[] map[i];
		}
		delete[] map;
		cout << "#" << t << " " << result << endl;
	}
}