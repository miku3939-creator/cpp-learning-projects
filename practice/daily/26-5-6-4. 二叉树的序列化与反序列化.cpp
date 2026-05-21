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

    string line(node *p)
    {
        string res;
        if (p == nullptr)
            return res + "#,";
        res += to_string(p->val);
        res += ",";
        res += line(p->lc);
        res += line(p->rc);
        return res;
    }
    void printmid(node *p)
    {
        if (p == nullptr)
            return;
        printmid(p->lc);
        cout << p->val << ' ';
        printmid(p->rc);
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
    res = t.line(t.r);
    if (!res.empty())
    {
        res.pop_back();
        cout << res << endl;
    }
    t.printmid(t.r);
    return 0;
}