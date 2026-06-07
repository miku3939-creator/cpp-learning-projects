/*5. 第八章第8题
【问题描述】

假设一个无向图采用邻接表G作为存储结构，设计一个算法判断其中是否存在经过顶点v的简单回路（环）。


【输入形式】

第一行输入邻接矩阵的维数n，接下来n行每行输入n个数字（0或1），为0代表不连通，为1代表连通；

第n+2行输入顶点v


【输出形式】

如果有经过顶点v的简单回路，输出TRUE

否则输出FALSE


【样例输入1】

4
0 1 0 1
1 0 1 0
0 1 0 0
1 0 0 0
0


【样例输出1】

FALSE



【样例输入2】

4
0 1 0 1
1 0 1 1
0 1 0 1
1 1 1 0
0



【样例输出2】

TRUE

*/

/*思路：
对V的邻居进行DFS
不许经过v
到达其他邻居则有环*/
#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
#include <queue>
using namespace std;
#define maxv 100
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
    vnode list[maxv];
    int a[maxv][maxv];
    graph(int n) : n(n) {}

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


/*myway
bool circle(graph &g, int v)
{
    anode *p = g.list[v].fa;
    int visited[maxv];
    int neib[maxv];
    int pre[maxv];
    for (int i = 0; i < g.n; i++)
    {
        pre[i] = i;
    }
    memset(visited, 0, g.n);
    memset(neib, 0, g.n);

    queue<int> q;
    while (p != nullptr)
    {
        int w = p->adjvex;
        neib[w] = 1;
        q.push(w);
        visited[w] = 1;
        p = p->nextarc;
    }

    while (!q.empty())
    {
        int w = q.front();
        q.pop();
        p = g.list[w].fa;
        while (p != nullptr)
        {
            int k = p->adjvex;
            if (k == v)
            {
                p = p->nextarc;
                continue;
            }
            else if (visited[k] != 1)
            {
                q.push(k);
                visited[k] = 1;
                pre[k] =pre[w];
            }
            else if (visited[k] == 1 && neib[k] == 1 && k != pre[w])
            {
                cout << "TRUE" << endl;
                return true;
            }
            p = p->nextarc;
        }
    }
    return false;
}*/
bool DFS(graph &g,int cur,int target,int ban,int visited[])
{
    if(cur==target)
        return true;

    visited[cur]=1;

    anode *p=g.list[cur].fa;

    while(p)
    {
        int w=p->adjvex;

        if(w!=ban && !visited[w])
        {
            if(DFS(g,w,target,ban,visited))
                return true;
        }

        p=p->nextarc;
    }

    return false;
}

bool circle(graph &g,int v)
{
    vector<int> nei;

    anode *p=g.list[v].fa;

    while(p)
    {
        nei.push_back(p->adjvex);
        p=p->nextarc;
    }

    for(int i=0;i<nei.size();i++)
    {
        for(int j=i+1;j<nei.size();j++)
        {
            int visited[maxv]={0};

            if(DFS(g,nei[i],nei[j],v,visited))
                return true;
        }
    }

    return false;
}
int main()
{
    int n, v;
    cin >> n;
    graph g(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> g.a[i][j];
        }
    }
    cin >> v;
    g.insert();
    if (!circle(g, v))
        cout << "FALSE" << endl;
    return 0;
}