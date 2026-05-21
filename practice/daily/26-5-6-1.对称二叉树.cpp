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
    int data;
    node() : lc(NULL), rc(NULL) {}
    node(int d) : lc(NULL), rc(NULL), data(d) {}
};
class tree
{
public:
    node *r;
    tree() : r(NULL) {}
    ~tree()
    {
        del(r);
        r = NULL;
    }
    void del(node *p)
    {
        if (p != NULL)
        {
            del(p->lc);
            del(p->rc);
            delete p;
        }
    }
    node *build(vector<int> &v, int &index)
    {
        if (index >= v.size())
            return nullptr;
        int val = v[index++];
        if (val == -1)
            return nullptr;
        node *p = new node(val);
        p->lc = build(v, index);
        p->rc = build(v, index);
        return p;
    }
    bool twins(node *p, node *q)
    {
        if (p == nullptr && q == nullptr)
            return true;
        if (p == nullptr || q == nullptr)
            return false;
        return (p->data == q->data) && twins(p->rc, q->lc) && twins(p->lc, q->rc);
    }
    bool twin()
    {
        if (r == nullptr)
            return true;
        return twins(r->lc, r->rc);
    }
};
int main()
{
    string line;
    int e, index = 0;
    vector<int> v;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    tree t;
    t.r = t.build(v, index);
    if (t.twin())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}