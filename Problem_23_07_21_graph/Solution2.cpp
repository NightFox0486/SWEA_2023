#ifndef _CRT_SECURE_NO_WARNINGS
#	define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

constexpr int POINT_POOL = 1000;

int  mapTable[10][10];
bool visited[10][10];

struct Point
{
	int    x, y, c;
	Point *next;
	Point *prev;
};

Point points[POINT_POOL];
int   pointCnt = 0;

Point *newPoint(int x, int y, int c)
{
	points[pointCnt].x    = x;
	points[pointCnt].y    = y;
	points[pointCnt].c    = c;
	points[pointCnt].next = nullptr;
	points[pointCnt].prev = nullptr;
	return &points[pointCnt++];
}

class Queue
{
private:
	Point *head;
	Point *tail;

public:
	int size;
	Queue() :
	    size(0),
	    head(nullptr),
	    tail(nullptr)
	{}

	void add(Point *point)
	{
		if (size == 0)
		{
			head = point;
			tail = point;
		}
		else
		{
			point->prev = tail;
			tail->next  = point;
			tail        = point;
		}
		size++;
	}
	Point *pop()
	{
		if (size == 0)
		{
			return nullptr;
		}
		else
		{
			Point *point = head;
			if (size == 1)
			{
				head = nullptr;
				tail = nullptr;
			}
			else
			{
				head       = head->next;
				head->prev = nullptr;
			}
			size--;
			return point;
		}
	}
};

int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

void init()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			visited[i][j] = false;
		}
	}
}

void bfs_init(int map_size, int map[10][10])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (i >= map_size || j >= map_size)
			{
				mapTable[i][j] = 1;
			}
			else
			{
				mapTable[i][j] = map[i][j];
			}
			visited[i][j] = false;
		}
	}
	for (int i = 0; i < 1000; i++)
	{
		points[i].x    = 0;
		points[i].y    = 0;
		points[i].next = nullptr;
		points[i].prev = nullptr;
		points[i].c    = 0;
	}
}
int bfs(int x1, int y1, int x2, int y2)
{
	init();
	int temp = y1;
	y1       = x1;
	x1       = temp;
	temp     = y2;
	y2       = x2;
	x2       = temp;
	x1 -= 1;
	y1 -= 1;
	x2 -= 1;
	y2 -= 1;
	Queue queue = Queue();
	queue.add(newPoint(x1, y1, 0));
	visited[x1][y1] = true;
	while (queue.size != 0)
	{
		Point *current = queue.pop();
		if (current->x == x2 && current->y == y2)
		{
			return current->c;
		}
		for (int i = 0; i < 4; i++)
		{
			int sx = current->x + dy[i];
			int sy = current->y + dx[i];
			if (sx >= 10 || sx < 0 || sy >= 10 || sy < 0 || mapTable[sx][sy] == 1 || visited[sx][sy])
				continue;
			visited[sx][sy] = true;
			queue.add(newPoint(sx, sy, current->c + 1));
		}
	}
	return -1;
}

static int test_bfs()
{
	int N;
	int map[10][10];
	scanf("%d", &N);
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
		{
			scanf("%d", &map[i][j]);
		}
	}
	bfs_init(N, map);
	int M;
	int score = 100;
	scanf("%d", &M);
	for (int i = 0; i < M; ++i)
	{
		int x1, y1, x2, y2;
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		int result = bfs(x1, y1, x2, y2);
		int dist;
		scanf("%d", &dist);
		if (result != dist)
			score = 0;
	}
	return score;
}

int main()
{
	setbuf(stdout, NULL);

	printf("#total score : %d\n", test_bfs());

	return 0;
}