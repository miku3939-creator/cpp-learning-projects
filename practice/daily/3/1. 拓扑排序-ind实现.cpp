/*1. 拓扑排序-DFS实现*
1. 拓扑排序-DFS实现
一、问题描述
给定一个有向无环图（DAG），使用DFS算法进行拓扑排序，输出一个合法的拓扑序。如果图中有环，输出"IMPOSSIBLE"。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 10000, 0 ≤ m ≤ 100000），表示节点数和边数。
接下来m行，每行两个整数u和v，表示从u到v有一条有向边。

三、输出形式
如果存在合法的拓扑序，输出n个整数，表示拓扑排序结果（逆后序）。
如果存在环，输出"IMPOSSIBLE"。

四、样例输入

6 6
1 2
1 3
2 4
3 4
4 5
4 6
五、样例输出

1 3 2 4 6 5
六、样例说明
DFS后序遍历结果，然后逆序得到拓扑序。

七、评分标准
共8个测试用例。

八、类库使用要求
可以使用vector。*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
struct anode
{
    anode *nextarc;
    int adjvex;
    anode(int a) : nextarc(nullptr), adjvex(a){}
};
struct vnode
{
    anode *fa;
    vnode() : fa(nullptr) {}
};
struct graph
{
    int n, e;
    vector<vnode> list;
    graph(int n, int e) : n(n), e(e)
    {
        list.resize(n + 1);
    }
    void insert(int i, int j)
    {
        if (list[i].fa == nullptr)
        {
            list[i].fa = new anode(j);
        }
        else
        {
            anode *p = new anode(j);
            p->nextarc = list[i].fa;
            list[i].fa = p;
        }
    }
    void tops()
    {
        stack<int> s;
        vector<int> ind(n + 1, 0);
        anode *p = nullptr;
        for (int i = 1; i <= n; i++)
        {
            p = list[i].fa;
            while (p != nullptr)
            {
                int w = p->adjvex;
                ind[w]++;
                p = p->nextarc;
            }
        }
        for (int i = 1; i <= n; i++)
        {
            if (ind[i] == 0)
                s.push(i);
        }
        while (!s.empty())
        {
            int i = s.top();
            s.pop();
            cout << i << ' ';
            p = list[i].fa;
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
};

int main()
{
    int n, e, u, v;
    cin >> n >> e;
    graph g(n, e);
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v;
        g.insert(u, v);
    }
    g.tops();
    return 0;
}