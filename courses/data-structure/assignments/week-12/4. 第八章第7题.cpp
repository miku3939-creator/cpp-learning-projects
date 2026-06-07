/*4. 第八章第7题
【问题描述】

一个连通图采用邻接表作为存储结构，设计一个算法实现从顶点v出发的深度优先遍历的非递归与递归过程。


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入顶点v


【输出形式】

第一行输出非递归过程遍历结果；

第一行输出递归过程遍历结果；


【样例输入1】

5
0 1 0 1 0
0 0 1 1 0
0 0 0 1 1
0 0 0 0 0
1 0 0 1 0
0


【样例输出1】

0 1 2 3 4

0 1 2 3 4



【样例说明】

由于输出的结果唯一，那么优先探索的顺序需要按照邻接表的顺序，不然会有多个结果



【考核说明】

全用递归过程而没有非递归过程会酌情扣分；

要求使用深度优先遍历

*/
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
using namespace std;
int visited[100];
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
    vector<vnode> list;
    vector<vector<int>> a;
    graph(int n) : n(n)
    {
        list.resize(n);
        a.resize(n, vector<int>(n, 0));
    }

    void insert()
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
            {
                if (a[i][j] != 0)
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
            }
    }
};

bool DFS0(graph &g, int v0)
{
    stack<int> s;
    visited[v0] = 1;
    s.push(v0);
    anode *p = g.list[v0].fa;
    if (p == nullptr)
        return false;
    cout << v0 << ' ';

    while (!s.empty())

    {
        bool find = false;
        int v = s.top();
        anode *p = g.list[v].fa;

        while (p != nullptr)
        {
            if (visited[p->adjvex] == 0)
            {
                int w = p->adjvex;
                cout << w << ' ';
                s.push(w);
                visited[w] = 1;
                find = true;
                break;
            }
            p = p->nextarc;
        }
        if (!find)
            s.pop();
    }
    return true;
}
void DFS(graph &g, int v)
{
    visited[v] = 1;
    cout << v << ' ';
    anode *p = g.list[v].fa;
    while (p != nullptr)
    {
        int w = p->adjvex;
        if (visited[w] == 0)
            DFS(g, w);
        p = p->nextarc;
    }
}

int main()
{
    int n, v;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            cin >> g.a[i][j];
        }
    cin >> v;
    g.insert();
    bool ok = DFS0(g, v);
    if (!ok)
    {
        cout << -1 << endl;
        return 0;
    }
    memset(visited, 0, sizeof(visited));
    cout << endl;
    DFS(g, v);
}