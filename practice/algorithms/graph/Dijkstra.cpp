#include <iostream>
using namespace std;
#define INF 0x3f3f3f3f
#define maxv 100

void print(int pre[],int i){
    if(i!=-1){
        print (pre,i-1);
        cout<<i<<' ';
    }

}
void Dijkstra(int g[maxv][maxv], int n, int v)
{
    int dist[maxv];  // 存原点到每个点的最短距离
    bool flag[maxv]; // 标记是否已确定
    int pre[maxv];
    for (int i = 0; i < n; i++)
    {
        dist[i] = g[v][i];
        flag[i]=0;
        if(g[v][i]!=INF)pre[i]=v;
        else pre[i]=-1;
    }
    flag[v] = 1;
    dist[v] = 0;
    // 每次找离原点最近的点
    for (int i = 1; i < n; i++)
    {
        int min = INF; // 存最小值
        int k = -1;    // 最小值对应的点
        for (int j = 0; j < n; j++)
        {
            if (flag[j] == 0 && dist[j] < min)
            {
                min = dist[j];
                k = j;
            }
        }
        if(k=-1)break;//防止不连通导致越界
        flag[k]=1;
        for(int j=0;j<n;j++){
            if(flag[j]==0&&g[k][j]<INF&&dist[k]+g[k][j]<dist[j]){
                dist[j]=dist[k]+g[k][j];
                pre[j]=k;
            }
        }
    }
    for(int i=0;i<n;i++){
        if(flag[i]==0){
            cout<<i<<"不可达"<<endl;
        }
        else{
            cout<<i<<"最短距离为"<<dist[i]<<endl;
        }
    }
}