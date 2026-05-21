#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    node(char v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr), val() {}
};
node *build(vector<char> &v, int &index)
{
    if (index >= v.size())
        return nullptr;
    char val = v[index++];
    if (val == '#')
        return nullptr;
    node *p = new node(val);
    p->lc = build(v, index);
    p->rc = build(v, index);
    return p;
}
void print(node *p)
{
    if (p == nullptr)
        return;
    if (p->rc == nullptr && p->lc == nullptr)
        cout << p->val << ' ';
    print(p->rc);
    print(p->lc);
}
int main()
{
    vector<char> v;
    string line;
    char e;
    int i = 0;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    node *r = build(v, i);
    print(r);

    return 0;
}