#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    int val;
    node(int v) : val(v), lc(nullptr), rc(nullptr) {}
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

    void printmid(node *p)
    {
        if (p == nullptr)
            return;
        printmid(p->lc);
        cout << p->val << ' ';
        printmid(p->rc);
    }
    void printrea(node *p)
    {
        if (p == nullptr)
            return;
        printrea(p->lc);
        printrea(p->rc);
        cout << p->val << ' ';
    }

    void printlayer()
    {
        if (r == nullptr)
            return;
        queue<node *> q;
        q.push(r);
        while (!q.empty())
        {
            node *p = q.front();
            q.pop();
            cout << p->val << ' ';
            if (p->lc != nullptr)
                q.push(p->lc);
            if (p->rc != nullptr)
                q.push(p->rc);
        }
    }
};
int main()
{
    string line, res;
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
    t.printmid(t.r);
    cout << endl;
    t.printrea(t.r);
    cout << endl;
    t.printlayer();
    cout << endl;
    return 0;
}