#include <iostream>
#include <map>
using namespace std;
int main()
{
    map<int, int> m;
    m.insert(pair<int, int>(1, 10));
    m.insert(make_pair(2, 20));
    m[3] = 30;
    m.insert({4, 40});

    for (auto &p : m)
    {
        cout << p.first << ": " << p.second << endl;
    }

    return 0;
}