#include <iostream>
using namespace std;

int fun4(int a, int b, int c, int d)
{
    int e = c;
    e -= b;
    d = c - b;
    d >> 31;
    e += d;
    d = e + b;
    if (d <= a)
    {
        e = 0;
        if (d >= a)
        {
            return e;
        }
        else
        {
            b = d + 1;
            fun4(a, b, c, d);
        }
    }
    else
    {
        c = d - 1;
        fun4(a, b, c, d);
        e += e;
        return e;
    }
}
int phase4(int a, int b, int c, int d)
{
    int s;
    d = s + 8;
    c = s + 12;
    b = 0x402821;
    int e = 0;
    if (e != 2)
    {
        cout<<"bomb";
    }
    else if (*(s + 12) <= 14)
    {
        c = 14;
        b = 0;
        a = s + 12;
        e = fun4(a, b, c, d);
        if (e != 4)
        {
          cout<<"bomb";
        }
        else
        {
            if (*(s + 8) == 4)
            {
                return e;
            }
        }
    }
    else{
       cout<<"bomb";
    }
}

int main()
{
}
