#include <iostream>
using namespace std;

template <typename T>
void swapab(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a, b;
    double c, d;
    cin >> a >> b >> c >> d;
    cout << 'a' << a << endl;
    cout << 'b' << b << endl;
    cout << 'c' << c << endl;
    cout << 'd' << d << endl;
    swapab(a, b);
    swapab(c, d);
    cout << 'a' << a << endl;
    cout << 'b' << b << endl;
    cout << 'c' << c << endl;
    cout << 'd' << d << endl;
    return 0;
}