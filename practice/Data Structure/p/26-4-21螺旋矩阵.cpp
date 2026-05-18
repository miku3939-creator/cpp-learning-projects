#include <iostream>
#include <vector>
using namespace std;
void spiral(int x, int y, int start, int n, vector<vector<int>> &a)
{
    if (n == 0){
        return;
    }
    if (n == 1)
    {
        a[x][y] = start;
        return;
    }
    for (int j = 0; j < n; j++)
    {
        a[x][y + j] = start++;}
    for (int i = 1; i < n; i++)
    {
        a[x + i][y + n - 1] = start++;
    }
    for (int j = n - 2; j >= 0; j--)
    {
        a[x + n - 1][y + j] = start++;
    }
    for (int i = n - 2; i > 0; i--)
    {
        a[x + i][y] = start++;
    }
    spiral(x + 1, y + 1, start, n - 2, a);
    return;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(n, 0));
    spiral(0, 0, 1, n, a);
    cout << n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}