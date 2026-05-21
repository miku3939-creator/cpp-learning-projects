#include <iostream>
using namespace std;
int n = 0;
bool mark[11][11];
int path[100][3];
int coutt = 0;
int dx[5] = {0, 0, 1, 0, -1};
int dy[5] = {0, 1, 0, -1, 0};
void print(int k)
{
    coutt++;
    cout << coutt << ':';
    for (int i = 1; i <= k; i++)
    {
        cout << '(' << path[i][1] << ',' << path[i][2] << ')';
        if (i != k)
            cout << "->";
    }
    return;
}

void dfs(int x, int y, int k)
{
    path[k][1] = x;
    path[k][2] = y;
    if (x == n && y == n)
    {
        cout << "!" ;
        print(k);
        cout<<endl;
    }
    for (int i = 1; i <= 4; i++)
    {
        int tx = x + dx[i];
        int ty = y + dy[i];
        if (mark[tx][ty] == false && tx >= 1 && tx <= n && ty >= 1 && ty <= n)
        {
            mark[tx][ty] = true;
            dfs(tx, ty, k + 1);
            mark[tx][ty] = false;
            path[k + 1][1] = 0;
            path[k + 1][2] = 0;
        }
    }
    cout<<'?';
    return;
}

int main()
{
    cin >> n;
    mark[1][1] = true;
    dfs(1, 1, 1);
    return 0;
}