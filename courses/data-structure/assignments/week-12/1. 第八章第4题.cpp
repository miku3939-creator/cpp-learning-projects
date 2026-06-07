/*1. 第八章第4题
【问题描述】
给定一个无向图 G，该图采用邻接表作为其存储结构。设计一个算法，计算并返回图 G 中连通分量的数量。连通分量定义为图中所有相互连通的顶点的最大子集，在无向图中，任意两个顶点之间都存在路径相连。

【输入形式】
输入包括两部分：

第一行包含两个整数 V 和 E，分别表示图中的顶点数和边数，其中 V≥1，E≥0。

接下来的 E 行，每行包含两个整数 u 和 v，表示顶点 u 和顶点 v 之间存在一条无向边。顶点编号从 1 到 V

【输出形式】
输出一个整数，表示图 G 中连通分量的数量。



【样例输入】

7 5
1 2
1 3
2 3
4 5
6 7
【样例输出】

3
【解释】
在给定的图中，有 7 个顶点和 5 条边，形成了以下连通分量：

顶点 1、2、3相互连通，形成一个连通分量。

顶点 4、5相互连通，形成第二个连通分量。

顶点 6、7 相互连通，形成第三个连通分量。
因此，图中共有 3 个连通分量。

【注意】

不是 O(nlogn) 以内的算法的话，可能会超时的呦！

*/
#include <iostream>
using namespace std;
#define MAXV 100
class anode
{
public:
    anode *nextarc;
    int adjvex;
    anode(int a) : nextarc(nullptr), adjvex(a) {}
};
class hnode
{
public:
    anode *fa;
    hnode() : fa(nullptr) {}
};
class graph
{
public:
    int n, e;
    hnode list[MAXV];
    graph(int n, int e) : n(n), e(e) {}
};
void insert(graph &g, int u, int v)
{
    anode *p = new anode(v);
    p->nextarc = g.list[u].fa;
    g.list[u].fa = p;

    p = new anode(u);
    p->nextarc = g.list[v].fa;
    g.list[v].fa = p;
}
void DFS(graph &g, int v, bool visited[])
{
    visited[v] = true;
    anode *p = g.list[v].fa;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFS(g, p->adjvex, visited);
        }
        p = p->nextarc;
    }
}
int count(graph &g)
{
    bool visited[MAXV] = {false};
    int cnt = 0;
    for (int i = 1; i <=g.n; i++)
    {
        if (!visited[i])
        {
            DFS(g, i, visited);
            cnt++;
        }
        }
    return cnt;
}
int main()
{
    int n, e, u, v;
    cin >> n >> e;
    graph g(n, e);
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v;
        insert(g, u, v);
    }
    cout << count(g) << endl;
}
