/*问题描述】


有N个网络结点，标记为1到N。给定一个列表times，表示信号经过有向边的传递时间，times[i]=(u，v，w)，其中u是源结点，v是目标结点，w是一个信号从源结点传递到目标结点的时间。现在我们向当前的结点K发送了一个信号，需要多久才能使所有结点都收到信号？如果不能使所有结点收到信号，返回-1。这里N的范围在[1，100]之间，K的范围在[1，N]之间，times的长度在[1，6000]之间，所有的边times[i]=(u，v，w)都有1≤u，v≤N且0≤w≤100。




要求设计满足题目要求的函数：

class Solution {
public:
 int networkDelayTime(vector<vector<int>>& times,int N,int K)
 {  …  }
};




【输入形式】

   输入网络结点的总个数N，以及信号发送的起始结点K。 然后输入时间列表，其中每一行给出了源结点、目标结点以及信号从源结点到目标结点锁需要的时间。


【输出形式】

    输出所有结点都收到信号需要花费的时间。



【样例输入】


4 2
2 1 1
2 3 1
3 4 1
【样例输出】

    2


【样例说明】

    时间列表对应的带权有向图如下图所示。网络有4个结点，信号从结点2开始传播，需要2个单位时间即可传递到所有的结点。测试数据存放在in.txt文件中。
















【评分标准】

    共10个测试用例，每通过一个测试得10分。*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include <vector>
using namespace std;
struct anode
{
    int adjvex;
    int w;
    anode *nextarc;
    anode(int a, int w) : adjvex(a), w(w), nextarc(nullptr) {}
};
struct vnode
{
    anode *fa;
    vnode() : fa(nullptr) {}
};
struct graph
{
    int n;
    vector<vnode> list;
    void insert(int u, int v, int w)
    {
        if (list[u].fa == nullptr)
        {
            list[u].fa = new anode(v,w);
        }
        else
        {
            anode *p = new anode(v,w);
            p->nextarc = list[u].fa;
            list[u].fa= p;
        }
    }
    graph(int n) : n(n)
    {
        list.resize(n);
    }
};

int networkDelayTime(graph& g, int n, int K) {
    vector<int> dist(n + 1, INT_MAX);
    vector<bool> visited(n + 1, false);
    dist[K] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, K});
    
    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (visited[u]) continue;
        visited[u] = true;
        
        anode *p = g.list[u].fa;
        while (p != nullptr) {
            int v = p->adjvex;
            int w = p->w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
            p = p->nextarc;
        }
    }
    
    int maxDist = 0;
    for (int i = 1; i <= n; i++) {
        if (dist[i] == INT_MAX) return -1;  // 有结点不可达
        if (dist[i] > maxDist) maxDist = dist[i];
    }
    return maxDist;
}
int main()
{
    ifstream in("in.txt");
    int n, sv, u, v, w;
    in >> n>>sv;
    graph g(n);
    in.ignore();
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        ss >> u >> v >> w;
        g.insert(u,v,w);
    }
    
    int result = networkDelayTime(g, n, K);
    cout << result << endl;
    
    return 0;
}
