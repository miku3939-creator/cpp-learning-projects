#include "26-5-17邻接表.cpp" //包含图(邻接矩阵)的基本运算算法
#include "5-21邻接矩阵.cpp"
#include <cstring>
using namespace std;
int visited[MAXV];
void DFS(adjgraph &G, int v)
{
    visited[v] = 1;
    cout << v << " ";
    anode *p = G.list[v].fa;
    while (p != nullptr)
    {
        int w = p->adjvex;
        if (visited[w] == 0)

            DFS(G, w);
        p = p->nextarc;
    }
}

void DFS(MatGraph &g,int v){
    visited[v] = 1;
    cout << v << " ";
    for(int w=0;w<g.n;w++){
        if(g.edges[v][w]!=0&&g.edges[v][w]!=INF){
            if(visited[w]==0){
                DFS(g,w);
            }
        }
    }
}
// 假设图 G 已经建立好，visited 数组已经初始化为 0
//非连通处理方式
void TraversalNonConnectedGraph(adjgraph &G)
{
    // 挨个顶点检查，G.n 是图的总顶点数
    for (int i = 0; i < G.n; i++)
    {
        if (visited[i] == 0) // 👈 关键检查：如果顶点 i 还没被摸过，说明发现新孤岛！
        {
            cout << "\n发现新连通块，从顶点 " << i << " 开始启动：\n";
            
            // 如果是求 DFS 全遍历，就调用：
            DFS(G, i); 
            
            // 如果是求 BFS 全遍历，就调用：
            // BFS(G, i); 
        }
    }
}