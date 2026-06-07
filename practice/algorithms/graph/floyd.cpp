#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define maxv 100
void floyd(int graph &g)
{
    int a[maxv][maxv];
    int path[maxv][maxv];
    for (int i = 0; i < g.n; i++)
    {
        for (int j = 0; j < g, n; j++)
        {
            a[i][j] = g.eadgs[i][j];
            if (i != j && g.edgs[i][j] < INF)
                path[i][j] = g.edgs[i][j];
            else
                path[i][j] = -1;
        }
    }

    for(int k=0;k<g.n;k++){
        for(int i=0;i<g.n;i++){
            for(int j=0;j<g.n;j++){
                if(a[i][j]>a[i][k]+a[k][j]){
                    a[i][j]=a[i][k]+a[k][j];
                    path[i][j]=path[j][k];
                }
            }
        }
    }
}