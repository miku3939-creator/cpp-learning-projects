#include "26-5-17邻接表.cpp" //包含图(邻接矩阵)的基本运算算法
#include "5-21邻接矩阵.cpp"
#include <cstring>
#include <queue>
using namespace std;

void BFS(adjgraph &G, int v)
{
    int visited[MAXV]={0};
    queue<int> q;
    cout << v << " ";
    visited[v] = 1;
    q.push(v);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        anode *p = G.list[u].fa;
        while (p != nullptr)
        {
            int w = p->adjvex;
            if (visited[w] == 0)
            {
                visited[w] = 1;
                cout << w << ' ';
                q.push(w);
            }
            p = p->nextarc;
        }
    }
}

void BFS(MatGraph &g, int v)
{
   int visited[MAXV]={0};
    memset(visited, 0, sizeof(visited));
    queue<int> q;
    cout << v << " ";
    visited[v] = 1;
    q.push(v);
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int w = 0; w < g.n; w++)
        {
            if (g.edges[v][w] != 0 && g.edges[v][w] != INF)
            {
                if (visited[w] == 0)
                {
                    visited[w] = 1;
                    cout << w << ' ';
                    q.push(w);
                }
            }
        }
    }
}
