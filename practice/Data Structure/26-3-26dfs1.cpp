#include <iostream>
#include <iomanip>
using namespace std;
void dfs0(int x, int y, int k, int (&a)[10][10])
{
    a[x][y] = k;
    if (y + 1 <= 4 && a[x][y + 1] == 0)
        dfs0(x, y + 1, k + 1, a);
    if (x + 1 <= 4 && a[x + 1][y] == 0)
        dfs0(x + 1, y, k + 1, a);
    if (y - 1 >= 1 && a[x][y - 1] == 0)
        dfs0(x, y - 1, k + 1, a);
    if (x - 1 >= 0 && a[x - 1][y] == 0)
        dfs0(x - 1, y, k + 1, a);
}

int n;
char a[30][30];
int path[410][3];

void print(int k){
for(int i=1;i<=k;i++){
cout<<'('<<path[i][1]<<','<<path[i][2]<<')';
if(i!=k)cout<<"->";
}
exit(0);
}

void dfs(int x,int y,int k){
    path[k][1]=x;
    path[k][2]=y;
    a[x][y]='1';
    if(x==n&&y==n){
        cout<<"!"<<endl;
        print(k);
    }
    if(a[x][y-1]=='0')dfs(x,y-1,k+1);
    if(a[x-1][y]=='0')dfs(x-1,y,k+1);
    if(a[x][y+1]=='0')dfs(x,y+1,k+1);
    if(a[x+1][y]=='0')dfs(x+1,y,k+1);
cout <<"?"<<' ';
}


int main()
{
    int a0[10][10] = {0};
    dfs0(1, 1, 1, a0);
    for (int i = 1; i <= 4; i++)
    {
        for (int j = 1; j <= 4; j++)
        {
            cout << setw(5) << a0[i][j];
        }
        cout << endl;
    }

    cin>>n;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cin>>a[i][j];
        }
    }
    dfs(1,1,1);
    return 0;
}