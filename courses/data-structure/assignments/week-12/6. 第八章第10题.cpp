/*6. 第八章第10题
【问题描述】

一个无向图采用邻接表存储，设计一个算法在存在经过顶点v的简单回路时输出所有这样的简单回路

【输入形式】

n m（点数、边数）

u1 v1(一条边连接u1和v1)

…

um vm

v(询问的顶点)

【输出形式】

将经过v的简单回路上的点按编号从小到大排序，并顺序输出，如

v1 v2 … vk (k为环长)

若有多条经过v的简单回路，将点编号排序后的回路按字典序从小到大排序，并输出，不同回路之间换行分隔

若没有经过v的简单回路，输出-1

【样例输入】

4 5
1 2
2 3
3 1
3 4
1 4
1

【样例输出】

1 2 3

1 2 3 4

1 3 4

【评分标准】

n<=200，无重边自环*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstring>
using namespace std;
#define maxv 200
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
set<vector<int>> s;
int sv;
void DFS(graph &g, int v)
{
    anode *p = g.list[v].fa;
    while (p != nullptr)
    {
        int w = p->adjvex;
        if (w == sv)
        {
            if (path.size() >= 3)
            {
                vector<int> cycle = path;
                sort(cycle.begin(), cycle.end());
                s.insert(cycle);
            }
        }
        else if (visited[w] == 0)
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
    cin>>n>>e;

    graph g(n);

    for (int i = 0; i < e; i++)
    {
        cin >> u >> v;
        g.insert(u, v);
        g.insert(v, u);
    }

    cin >> sv;
    visited[sv] = 1;
    path.push_back(sv);
    DFS(g, sv);

    if (s.empty())
    {
        cout << -1;
        return 0;
    }

    for (vector<int> v : s)
    {
        for (int i = 0; i < v.size(); i++)
        {
            cout << v[i] << ' ';
        }
        cout << endl;
    }
    return 0;
}