#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
class dat
{
public:
    int x;
    int y;
    int val;
    dat() {}
    dat(int x, int y, int v) : x(x), y(y), val(v) {}
};
int main()
{
    ifstream in("in.txt");
    ofstream out("abc.out");
    int x, y, n, a, b, e;
    in >> x >> y >> n;
    dat *d = new dat[n];
    for (int i = 0; i < n; i++)
    {
        in >> a >> b >> e;
        dat j(b, a, e);
        d[i] = j;
    }
    sort(d, d + n, [](dat a, dat b)
         { if (a.x != b.x) return a.x < b.x;
           return a.y < b.y; });
    out << y << ' ' << x << ' ' << n << endl;
    for (int i = 0; i < n; i++)
    {
        out << d[i].x << ' ' << d[i].y << ' ' << d[i].val << endl;
    }
    delete[] d;
    in.close();
    out.close();
    return 0;
}