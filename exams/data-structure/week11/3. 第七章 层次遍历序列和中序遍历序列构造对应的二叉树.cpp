#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_set>
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
string findset(string &l, unordered_set<char> &set)
{
    string res;
    for (char c : l)
    {
        if (set.count(c))
            res += c;
    }
    return res;
}
node *buildtree(string &l, string &m)
{
    if (l.empty() || m.empty())
        return nullptr;
    char data = l[0];
    node *r = new node(data);

    int pos = m.find(data);
    string le = m.substr(0, pos);
    string ri = m.substr(pos + 1);
    unordered_set<char> lef(le.begin(), le.end());
    unordered_set<char> rig(ri.begin(), ri.end());

    string lel = findset(l, lef);
    string ril = findset(l, rig);

    r->lc = buildtree(lel, le);
    r->rc = buildtree(ril, ri);
    return r;
}
void print(node *p)
{
    if (p == nullptr)
        return;
    cout << p->val << ' ';
    print(p->lc);
    print(p->rc);
}
int main()
{
    string l, m;
    string line;
    char e;
    int n;
    cin>>n;
    cin.ignore();
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        l.push_back(e);
    }
    getline(cin, line);
    stringstream s(line);
    while (s >> e)
    {
        m.push_back(e);
    }

    node *r = buildtree(l, m);

    print(r);
    return 0;
}