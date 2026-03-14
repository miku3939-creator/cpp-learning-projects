#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n, q;
    cin >> n >> q;
    vector<vector<int>> v(n);
    for (int a = 0; a < q; a++)
    {
        int choice, i, j, k;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cin >> i >> j >> k;
            if (v[i].size() <= j)
                v[i].resize(j + 1);
            v[i][j] = k;
            break;
        }
        case 2:
        {

            cin >> i >> j;
            cout << v[i][j] << endl;
            ;
            break;
        }
        }
    }
    return 0;
}