#include <iostream>
#include <cstring>
using namespace std;
#define MAXV 100
#define INF 0x3f3f3f3f
struct graph
{
    int n, e;
    int edges[MAXV][MAXV];
    graph(int n, int e) : n(n), e(e)
    {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (i == j)
                    edges[i][j] = 0;
                else
                    edges[i][j] = INF;
            }
    }
};
int prim(graph g, int v)
{
    int lowcost[MAXV];
    int lead[MAXV];
    int sum = 0;
    for (int i = 1; i <= g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        lead[i] = v;
    }
    for (int i = 1; i < g.n; i++)
    {
        int min = INF;
        int k = -1;
        for (int j = 1; j <= g.n; j++)
            if (lowcost[j] < min && lowcost[j] != 0)
            {
                min = lowcost[j];
                k = j;
            }
        if (k == -1)
            return -1;
        sum += min;

        lowcost[k] = 0;
        for (int j = 1; j <= g.n; j++)
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j] && lowcost[j] != 0)
            {
                lowcost[j] = g.edges[k][j];
                lead[j] = k;
            }
    }

    return sum;
}
int main()
{
    int n, e, u, v, w;
    cin >> n >> e;
    graph g(n, e);
    for (int i = 0; i < e; i++)
    {
        cin >> u >> v >> w;
        g.edges[u][v] = w;
        g.edges[v][u] = w;
    }
    cout << prim(g, 1) << endl;
    return 0;
}