/*1. 判断最小生成树唯一性
判断最小生成树唯一性
一、问题描述
给定一个带权无向连通图，判断其最小生成树（MST）是否唯一。如果唯一，输出"YES"和MST的总权重；如果不唯一，输出"NO"和最小MST的总权重。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 100, 1 ≤ m ≤ 1000），表示节点数和边数。
接下来m行，每行三个整数u、v、w，表示节点u和v之间有一条权重为w的边。

三、输出形式
如果MST唯一，输出"YES"和总权重，空格分隔。
如果MST不唯一，输出"NO"和最小总权重，空格分隔。

四、样例输入1

4 5
1 2 1
1 3 4
2 3 2
2 4 5
3 4 3
五、样例输出1

YES 6
六、样例输入2

4 5
1 2 1
1 3 1
2 3 1
2 4 1
3 4 1
七、样例输出2

NO 3
八、样例说明
样例1：MST包含边(1,2,1), (2,3,2), (3,4,3)，唯一。
样例2：所有边权重都是1，存在多个MST，总权重都是3。

九、评分标准
共10个测试用例。

十、类库使用要求
可以使用vector、algorithm。使用并查集。*/
#include <iostream>
#include <vector>
using namespace std;
class edge
{
public:
    int u, v;
    int w;
    int id;
};

// 排序
void merge(vector<edge> &a, int l, int mid, int r)
{
    vector<edge> p(r - l + 1);
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
void mergeSort(vector<edge> &a, int l, int r)
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
int find(vector<int> &p, int x)
{
    if (x == p[x])
        return x;
    else
        return p[x] = find(p, p[x]);
}

int kruskal(vector<edge> e, int n, int m, vector<edge> &MST)
{
    mergeSort(e, 0, m - 1);
    vector<int> p(n+1);
    int sum = 0; // 最小边权和
    for (int i = 1; i < n + 1; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int pu = find(p, e[i].u);
        int pv = find(p, e[i].v);
        if (pu != pv)
        {
            p[pv] = pu;
            sum += e[i].w;
            MST.push_back(e[i]);
        }
    }
    return sum;
}
int kruskal(vector<edge> e, int n, int m, int id)
{
    mergeSort(e, 0, m-1);
    vector<int> p(n+1);
    int sum = 0; // 最小边权和
    for (int i = 1; i < n+1; i++)
    {
        p[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        if (e[i].id==id)
            continue;
        int pu = find(p, e[i].u);
        int pv = find(p, e[i].v);
        if (pu != pv)
        {
            p[pv] = pu;
            sum += e[i].w;
        }
    }
    return sum;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<edge> e(m); // 边数组
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].id=i;
    }
    vector<edge> MST;
    int sum0 = kruskal(e, n, m, MST);

    for (auto E:MST)
    {
        if (sum0 == kruskal(e, n, m,E.id))
        {
            cout << "NO" << ' ' << sum0;
            return 0;
        }
    }
    cout << "YES" << ' ' << sum0;
    return 0;
}