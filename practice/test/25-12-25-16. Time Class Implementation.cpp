#include <iostream>
using namespace std;
class Time
{
public:
    int h;
    int m;
    int s;
    Time &operator++()
    {
        s++;
        if (s >= 60)
        {
            m += s / 60;
            s %= 60;
        }
        if (m >= 60)
        {
            h += m / 60;
            m %= 60;
        }
        if (h >= 24)
            h %= 24;
        return *this;
    }
    Time operator++(int)
    {
        Time temp(*this);
        ++(*this);
        return temp;
    }
    Time &operator--()
    {
        s--;
        if (s < 0)
        {
            m -= 1;
            s += 60;
        }
        if (m  <0)
        {
            h -= 1;
            m += 60;
        }
        if (h < 0)
            h += 24;
        return *this;
    }
    Time operator--(int)
    {
        Time temp(*this);
        --(*this);
        return temp;
    }
    Time &operator+=(const Time &p)
    {
        s += p.s;
        m += p.m;
        h += p.h;
        if (s >= 60)
        {
            m += s / 60;
            s %= 60;
        }
        if (m >= 60)
        {
            h += m / 60;
            m %= 60;
        }
        if (h >= 24)
            h %= 24;
        return *this;
    }
    Time &operator-=(const Time &p)
    {
        s -= p.s;
        m -= p.m;
        h -= p.h;
        if (s <0)
        {
            m -= 1;
            s += 60;
        }
        if (m  <0)
        {
            h -= 1;
            m += 60;
        }
        if (h < 0)
            h += 24;

        return *this;
    }
    Time(int h, int m, int s) : h(h), m(m), s(s) {}
    Time() {}
};
istream &operator>>(istream &in, Time &p)
{
    in >> p.h >> p.m >>p.s;
    return in;
}
ostream &operator<<(ostream &out, const Time &p)
{
    if (p.h < 10)
        out << 0;
    out << p.h << ':';
    if (p.m < 10)
        out << 0;
    out << p.m << ':';
    if (p.s < 10)
        out << 0;
    out << p.s ;
    return out;
}
int main()
{
     Time time1, time2;
    
    // 输入时间
    cin >> time1 >> time2;
    
    // 执行各种运算并输出
    time1 += time2++;
    cout << time1 << endl;
    
    time1 -= time2;
    cout << time1 << endl;
    
    ++time2;
    cout << time2 << endl;
    
    time2 += time1--;
    cout << time2 << endl;
    
    --time1;
    cout << time1 << endl;
    
    time2 -= time1;
    cout << time2 << endl;
}
