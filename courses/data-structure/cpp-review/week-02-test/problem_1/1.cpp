#include<iostream>
using namespace std;
template <typename T>
class Pair {
    T a, b;
public:
    Pair(T x, T y): a(x), b(y) {}
    T sum() { return a + b; }
};
