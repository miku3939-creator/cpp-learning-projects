#include "5-21邻接矩阵.cpp"
using namespace std;
void prim(MatGraph g, int v)
{
    int lowcost[MAXV];
    int lead[MAXV];
    for (int i = 0; i < g.n; i++)
    {
        lowcost[i] = g.edges[v][i];
        lead[i] = v;
    }
    for (int i = 1; i < g.n; i++)
    {
        int min = INF;
        int k = -1;
        for (int j = 0; j < g.n; j++)
            if (lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
        cout << "  边(" << lead[k] << "," << k << "),权为" << min << endl;
        lowcost[k] = 0;
        for (int j = 0; j< g.n; j++)
            if (g.edges[k][j] != 0 && g.edges[k][j] < lowcost[j] && lowcost[j] != 0)
            {
                lowcost[j] = g.edges[k][j];
                lead[j] = k;
            }
    }
}