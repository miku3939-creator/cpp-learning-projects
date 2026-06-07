#include <iostream>
#include <stack>
using namespace std;
#define INF 0x3f3f3f3f
#define maxv 100
class anode // 边结点类型
{
public:
    int adjvex; // 邻接点
    int weight;
    anode *nextarc; // 指向下一条边的边结点
};
class hnode // 头结点类型
{
public:
    string info; // 顶点信息
    anode *fa;   // 指向第一条边的边结点
};
class graph // 图邻接表类
{
public:
    int n, e;         // 顶点数，边数
    hnode list[maxv]; // 头结点数组

    graph()
    {
        for (int i = 0; i < maxv; i++)
        {
            list[i].fa == nullptr;
        }
    }
};
void tops(graph &g)
{
    stack<int> s;
    int ind[maxv];
    anode *p;
    for (int i = 0; i < g.n; i++)
    {
        p = g.list[i].fa;
        while (p != nullptr)
        {
            int w = p->adjvex;
            ind[w]++;
            p = p->nextarc;
        }
    }
    for (int i = 0; i < g.n; i++)
    {
        if (ind[i] == 0)
            s.push(i);
    }
    while (!s.empty())
    {
        int i = s.top();
        s.pop();
        cout << i << ' ';
        p = g.list[i].fa;
        while (p != nullptr)
        {
            int w = p->adjvex;
            ind[w]--;
            if (ind[w] == 0)
                s.push(w);
            p = p->nextarc;
        }
    }
}