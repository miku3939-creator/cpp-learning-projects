#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class task
{
public:
    int at;
    int et;
    task(int a, int e) : at(a), et(e) {}
};
int main()
{
    int n, a, b, t = 0, wt = 0;
    vector<task> v;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a >> b;
        v.push_back(task(a, b));
    }
    sort(v.begin(), v.end(), [](task a, task b)
         { return a.at < b.at; });
    for (int i = 0; i < n; i++)
    {
        if (v[i].at < t)
        {
            wt += t;
            wt -= v[i].at;
        }
        if (v[i].at > t)
            t = v[i].at;
        t += v[i].et;
    }
    cout << wt << endl;
    return 0;
}