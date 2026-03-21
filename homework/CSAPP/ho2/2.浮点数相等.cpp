#define EPSILON 1e-6f
#include <iostream>
using namespace std;
bool AlmostEqualABS(float x, float y)
{
    float diff = x - y;
    return diff <= EPSILON;
}
int main()
{
    float x, z;
    float y;
    cin >> x >> z >> y;
    x += z;
    cout << AlmostEqualABS(x, y) << endl;
    cout<<sizeof(float)<<endl;
    return 0;
}