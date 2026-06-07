
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

#define MAXV 100       // 图中最多的顶点数
#define INF 0x3f3f3f3f // 用INF表示无穷大

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
class adjgraph // 图邻接表类
{
public:
    int n, e;         // 顶点数，边数
    hnode list[MAXV]; // 头结点数组

    adjgraph()
    {
        for (int i = 0; i < MAXV; i++)
        {
            list[i].fa == nullptr;
        }
    }

    ~adjgraph()
    {
        anode *p, *q;
        for (int i = 0; i < n; i++)
        {
            p = list[i].fa;
            while (p != nullptr)
            {
                q = p->nextarc;
                delete p;
                p = q;
            }
        }
    }
    void create1(int a[][MAXV], int n, int e) // 通过边数组a、顶点数n和边数e来建立图的邻接表
    {
        this->n = n;
        this->e = e;
        anode *p;
        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                if (a[i][j] != 0 && a[i][j] != INF)
                {
                    p = new anode();
                    p->adjvex = j;
                    p->weight = a[i][j];
                    p->nextarc = list[i].fa;
                    list[i].fa = p;
                }
            }
        }
    }

    void print()
    {
        anode *p;
        for (int i = 0; i < n; i++)
        {
            cout << i << ' ';
            p = list[i].fa;
            while (p != nullptr)
            {
                cout << "->";
                cout << '(' << p->adjvex << ',' << p->weight << ')' << endl;
                p = p->nextarc;
            }
        }
    }
};

/*#define MAXE 200
int head[MAXV]; // 头结点数组head[u]：是一个记录官，它只负责死死记住当前起点 u 发出的“最新、排在第一位”的那条边在 edges 数组里的下标。
class edge
{
public:         // 边结点类型
    int adjvex; // 邻接点
    int weight; // 权值
    int next;   // 下一个边结点在edges数组中的下标
};
edge edges[MAXV];
int n;   // 顶点数
int cnt; // edges数组元素个数

void addedge(int i, int j, int w)
{
    edges[cnt].adjvex = v;
    edges[cnt].weight = w;
    edges[cnt].next = head[u]; // 将edges[cnt]边结点插入到head[u]的表头
    head[u] = cnt;
    cnt++;
}
void init() // 初始化
{
    cnt = 0;                            // cnt从0开始
    memset(head, 0xffff, sizeof(head)); // 所有元素初始化为-1
}

void CreateAdjGraph(vector<vector<int>> a, int n) // 通过边数组a和顶点数n建立简化邻接表
{                                                 // a中每个元素表示一条边<u,v,w>
    init();                                       // 初始化简化邻接表
    for (int i = 0; i < a.size(); i++)
        addedge(a[i][0], a[i][1], a[i][2]); // 插入一条边
}

void DispAdjGraph() // 输出图的邻接表
{
    for (int i = 0; i < n; i++) // 遍历每个头结点
    {
        printf("   [%d]", i);
        for (int j = head[i]; j != -1; j = edges[j].next)
            printf(" (%d,%d,%d)", edges[j].adjvex, edges[j].weight, edges[j].next);
        printf("\n");
    }
}*/
