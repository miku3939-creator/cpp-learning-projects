/*4. 第八章 狄克斯特拉算法
【问题描述】
给定一个带权无向图，采用邻接矩阵形式存储。设计并实现一个基于狄克斯特拉算法思想的程序，求从顶点s到顶点t的最短路径长度。



【输入形式】
第一行为两个整数N和M（2 ≤ N ≤ 100），分别表示图中节点的数量以及边的数量。接下来N行，每行包含N个非负整数，描述邻接矩阵中的权重，其中0表示当前顶点与该列顶点没有直接相连或为同一顶点，其它值表示从当前顶点到该列顶点的权重。最后两行为两个整数s和t（1 ≤ s, t ≤ N），分别代表起点和终点。



【输出形式】
一个整数，表示从顶点s到顶点t的最短路径长度。路径不存在时，输出-1。



【输入样例】
5 7
0 3 12 4 0
3 0 6 5 0
12 6 0 0 2
4 5 0 0 8
0 0 2 8 0
1
5



【输出样例】
11

*/
#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define maxv 100

void Dijkstra(int g[maxv][maxv], int n, int v, int u)
{
    int dist[maxv];  // 存原点到每个点的最短距离
    bool flag[maxv]; // 标记是否已确定
    for (int i = 1; i <= n; i++)
    {
        if (g[v][i] == 0)
        {
            if (v == i)
                dist[i] = 0;
            else dist[i] = INF;
        }
        else
            dist[i] = g[v][i];
        flag[i] = 0;
    }
    flag[v] = 1;
    dist[v] = 0;
    // 每次找离原点最近的点
    for (int i = 1; i < n; i++)
    {
        int min = INF; // 存最小值
        int k = -1;    // 最小值对应的点
        for (int j = 1; j <= n; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        if (k == -1)
            break; // 防止不连通导致越界
        flag[k] = 1;
        for (int j = 1; j <= n; j++)
        {
            if (flag[j] == 0 &&g[k][j] != 0&& dist[k] + g[k][j] < dist[j])
            {
                dist[j] = dist[k] + g[k][j];
            }
        }
    }
    if (dist[u] == INF)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << dist[u] << endl;
    }
}
int main()
{
    int n, e, w, u, v;
    cin >> n >> e;
    int g[maxv][maxv];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> w;
            g[i][j] = w;
        }
    cin >> u >> v;
    Dijkstra(g, n, u, v);
    return 0;
}