/*2. 骑士最少步数问题
【问题描述】

国际象棋中的骑士，每一步有八种走法，如下图所示：

向左走一格，向上走两格；

向右走一格，向上走两格；

向左走一格，向下走两格；

向右走一格，向下走两格

向左走两格，向上走一格；

向左走两格，向下走一格；

向右走两格，向上走一格；

向右走两格，向下走一格

国际象棋 _副本.png

给定8*8的棋盘，用字母a~h表示列，数字1~8表示行。棋盘上任意一个格子的位置可由一个字母和一个数字组成的字符串表示。例如，图示中骑士所在位置为d4，它一步可达的8个位置分别为c2, e2,c6, e6, b3, b5, f3, f5。你的任务是写一个程序，对于棋盘上任一两个位置x和y，计算骑士从位置x移动到位置y最少需要移动多少步。



【输入形式】

输入为两个位置，依次代表起点（第一个位置）和终点（第二个位置）。每个位置由一个表示列的字母（a~h）和一个表示行的数字（1~8）表示，字母和数字之间没有空格，两个位置之间用空格隔开。

【输出形式】

输出一个整数，表示骑士从起点位置到终点位置最少需要移动的步数。#include<iostream>
*/
#include <queue>
#include <iostream>
#include <cstring>
#define N 8
using namespace std;
struct node
{
    int x, y;
};
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
int bfs(int x1, int y1, int x2, int y2)
{
    queue<node> q;
    q.push({x1, y1});
    int dist[N][N] = {0};
    memset(dist, -1, sizeof(dist));
    dist[x1][y1] = 0;
    while (q.size())
    {
        auto u = q.front();
        q.pop();
        if (u.x == x2 && u.y == y2)
        {
            return dist[u.x][u.y];
        }

        for (int i = 0; i < 8; i++)
        {
            int a = u.x + dx[i], b = u.y + dy[i];
            if (a < 0 || b < 0 || a >= 8 || b >= 8)
                continue;
            if (dist[a][b] != -1)
                continue;
            dist[a][b] = dist[u.x][u.y] + 1;
            q.push({a, b});
        }
    }
}
int main()
{
    string a, b;
    int x1, y1, x2, y2, i;
    cin >> a >> b;
    x1 = a[0] - 'a';
    x2 = b[0] - 'a';
    y1 = a[1] - '1';
    y2 = b[1] - '1';
    i = bfs(x1, y1, x2, y2);
    cout << i << endl;
    return 0;
}