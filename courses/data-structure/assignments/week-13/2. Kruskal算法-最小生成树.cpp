/*Kruskal算法-最小生成树
一、问题描述
给定一个带权无向连通图，使用Kruskal算法求最小生成树（MST）的总权重。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 1000, 1 ≤ m ≤ 100000），表示节点数和边数。
接下来m行，每行三个整数u、v、w，表示节点u和v之间有一条权重为w的边。

三、输出形式
输出一个整数，表示最小生成树的总权重。如果图不连通，输出-1。*/#define maxe 100
#include <iostream>
#define maxe 10000
using namespace std;
class edge
{
public:
    int u, v;
    int w;
};

// 排序
void merge(edge a[], int l, int mid, int r)
{
    edge *p = new edge[r-l + 1];
    int i = l, j = mid + 1, k = 0;
    while (i <= mid && j <= r)
    {
        if (a[i].w <= a[j].w)
        {
            p[k++] = a[i++];
        }
        else
            p[k++] = a[j++];
    }
    while (i <= mid)
    {
        p[k++] = a[i++];
    }
    while (j <= r)
    {
        p[k++] = a[j++];
    }
    for (i = l, k = 0; i <= r; i++, k++)
    {
        a[i] = p[k];
    }
}
void mergeSort(edge a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l + r) / 2;
        mergeSort(a, l, mid);
        mergeSort(a, mid + 1, r);
        merge(a, l, mid, r);
    }
}

// 并查集
int find(int p[], int x)
{
    if (x == p[x])
        return x;
    else
        return p[x] = find(p, p[x]);
}

int kruskal(edge e[], int n, int m)
{
    mergeSort(e, 0, m-1);
    int p[maxe];
    int sum=0;//最小边权和
    int cnt=0;
    for (int i = 1; i < n+1; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int pu = find(p, e[i].u);
        int pv = find(p, e[i].v);
        if(pu!=pv){
            p[pv]=pu;
            sum+=e[i].w;cnt++;
        }
    }
    if(cnt!=n-1)return -1;
    return sum;
}

int main()
{
    edge e[maxe]; // 边数组
    int n, m;
    cin >>n>>m;
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
    }
    cout<<kruskal(e,n,m)<<endl;
}