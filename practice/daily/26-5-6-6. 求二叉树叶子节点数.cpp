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
    node *build(vector<int> &v, int &i)
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

    int leaf(node *p)
    {
        if(p==nullptr)return 0;
        if (p->lc == nullptr && p->rc == nullptr)
            return 1;
        return leaf(p->lc) + leaf(p->rc);
    }
};
int main()
{
    string line;
    int e, i = 0;
    vector<int> v;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    tree t;
    t.r = t.build(v, i);
    cout << t.leaf(t.r)<<endl;
    return 0;
}