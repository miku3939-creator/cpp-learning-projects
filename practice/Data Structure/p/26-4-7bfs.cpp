#include <iostream>
#include <queue>
#define N 20
using namespace std;
int n,g[N][N];
struct node{int x,y;};
node pre [N][N];
int dx[4]={-1,0,1,0};
int dy[4]={0,1,0,-1};
void bfs(int x,int y)
{
    queue<node>q;
    q.push({x,y});
    g[x][y]=1;
    while(q.size()){
        auto u=q.front();q.pop();
        for(int i=0;i<4;i++){
            int a=u.x+dx[i],b=u.y+dy[i];
            if(a<0||a>=n||b<0||b>=n)continue;
            if(g[a][b])continue;
            g[a][b]=1;
            pre[a][b]=u;
            q.push({a,b});
        }
    }
}
void print (int x,int y){
    if(x==0&&y==0)return ;
    node p=pre[x][y];
    print(p.x,p.y);
    cout<<x<<' '<<y<<endl;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>g[i][j];
        }
    }
    bfs(0,0);
    puts("0 0");
    print(n-1,n-1);
    return 0;
}