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
    int val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
};
class tree
{
public:
    node *r;
    tree() : r(nullptr) {}
    ~tree()
    {
        del(r);
        r = nullptr;
    }
    void del(node *p)
    {
        if (p != nullptr)
        {
            del(p->lc);
            del(p->rc);
            delete p;
        }
    }
    node *build(vector<int> v, int &i)
    {
        if (i >= v.size())
            return nullptr;
        int val = v[i++];
        if (val == -1)
            return nullptr;
        node *p = new node(val);
        p->lc = build(v, i);
        p->rc = build(v, i);
        return p;
    }
    node *find(int a, int b, node *p)
    {
        if (p == nullptr)
            return nullptr;
        if (p->val == a || p->val == b)
            return p;
        node *left = find(a, b, p->lc);
        node *right = find(a, b, p->rc);

        if (left != nullptr && right != nullptr)
            return p;
        if (left != nullptr)
            return left;
        if (right != nullptr)
            return right;
        return nullptr;
    }
};
int main()
{
    int a, b, e, i = 0;
    string line;
    vector<int> v;
    tree t;
    cin >> a >> b;
    cin.ignore();
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    t.r = t.build(v, i);
    if (t.find(a, b, t.r) != nullptr)
        cout <<t.find(a, b, t.r)->val << endl;
    else
        cout << -1 << endl;
    return 0;
}