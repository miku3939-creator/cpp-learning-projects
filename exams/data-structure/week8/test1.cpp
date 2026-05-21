#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int m, n;
    cin >> m >> n;
    if (m != n)
    {
        cout << "false" << endl;
        return 0;
    }
    cout<<"true"<<endl;
    vector<vector<int>> a(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            swap(a[i][j], a[j][i]);
        }
    }

        for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << a[i][j]<<' ';
        }
        cout<<endl;
    }
return 0;
}