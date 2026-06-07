/*【问题描述】假设一个有向图采用邻接表 G 作为存储结构，请设计一个算法，给定起点 S 和终点 T，输出不经过重复顶点的所有简单路径（即不包含回路的路径）。

【输入形式】

第一行输入两个整数 V 和 E，分别表示图的顶点数和边数（1 ≤ V ≤ 20，0 ≤ E ≤ V*(V-1)）。

第二行输入两个整数 S 和 T，分别表示起点和终点（1 ≤ S, T ≤ V，S ≠ T）。

接下来 E 行，每行输入两个整数 u v，表示有向边 u → v。

【输出形式】

每行输出一条从 S 到 T 的简单路径，路径中的顶点用空格分隔。

如果不存在这样的路径，输出 No Path。

路径顺序按字典序升序（即先访问编号小的顶点）。

【样例输入】

5 6

1 5

1 2

1 3

2 4

2 5

3 4

4 5

【样例输出】

1 2 4 5

1 2 5

1 3 4 5

【样例说明】
【评分标准】*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
#define maxv 100
int visited[maxv];
struct anode
{
    int adjvex;
    anode *nextarc;
    anode(int a) : adjvex(a), nextarc(nullptr) {}
};
struct vnode
{
    anode *fa, *la;
    vnode() : fa(nullptr), la(nullptr) {}
};
struct graph
{
    int n, e;
    vnode list[maxv];
    graph(int n) : n(n) {}

    void insert(int i, int j)
    {
        if (list[i].fa == nullptr)
        {
            list[i].fa = new anode(j);
            list[i].la = list[i].fa;
        }
        else
        {
            anode *p = new anode(j);
            list[i].la->nextarc = p;
            list[i].la = p;
        }
    }
};

vector<int> path;
set<vector<int>> a;
int s, t;

void DFS(graph &g, int v)
{

    if (v == t)
    {
        a.insert(path);
        return;
    }
    anode *p = g.list[v].fa;
    while (p != nullptr)
    {
        int w = p->adjvex;
        if (visited[w] == 0)
        {
            visited[w] = 1;
            path.push_back(w);
            DFS(g, w);
            visited[w] = 0;
            path.pop_back();
        }

        p = p->nextarc;
    }
}
int main()
{
    int n, e, u, v;
    cin >> n >> e;

    graph g(n);
    cin >> s >> t;
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v;
         g.insert(u, v);
    }

    visited[s] = 1;
    path.push_back(s);
    DFS(g, s);

    if (a.empty())
    {
        cout << "No Path" << endl;
        return 0;
    }

    for (vector<int> v : a)
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}