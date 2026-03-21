#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
    for (int i = 0; i < n / 2; i++)
    {
        swap(v[i], v[n - i - 1]);
    }
    for (int i = 0; i < n; i++)
    {
        cout<<v[i]<<' ';
    }
    cout<<endl;
    return 0;
}