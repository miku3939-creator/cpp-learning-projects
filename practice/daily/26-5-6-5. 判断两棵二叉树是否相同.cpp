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
};
int main()
{
    string line, res1, res2;
    int e, i = 0;
    vector<int> v1, v2;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v1.push_back(e);
    }
    getline(cin, line);
    stringstream s(line);
    while (s >> e)
    {
        v2.push_back(e);
    }
    tree t1, t2;
    t1.r = t1.build(v1, i);
    i = 0;
    t2.r = t2.build(v2, i);
    res1 = t1.line(t1.r);
    res2 = t2.line(t2.r);
    if (res1 == res2)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}