#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <queue>
#include <map>
using namespace std;
class node
{
public:
    char val;
    double wei;
    node *lc;
    node *rc;

    node() {}
    node(char c, double w) : val(c), wei(w),lc(nullptr),rc(nullptr) {}
    node(double d, node *l, node *r) : val(127), wei(d), lc(l), rc(r) {}
};

struct mys
{
    bool operator()(node *a, node *b)
    {
        if (a->wei != b->wei)
            return a->wei > b->wei;
        return a->val > b->val; 
    }
};

string decode(node *r, string s)
{
    string res;
    node *cur = r;
    for (char bit : s)
    {
        if (bit == '0')
            cur = cur->lc;
        else
            cur = cur->rc;
        if (cur->lc == nullptr && cur->rc == nullptr)
        {
            res += cur->val;
            cur = r;
        }
    }
    return res;
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

int main()
{
    int n, c;
    double d;
    string s;
    priority_queue<node *, vector<node *>, mys> pq;
    ifstream in("in.txt");
    ofstream out("out.txt");
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> s;
        size_t pos = s.find(':');
        c = s[0];
        d = stod(s.substr(pos + 1));
        pq.push(new node(c, d));
    }

    while (pq.size() > 1)
    {
        node *l = pq.top();
        pq.pop();
        node *r = pq.top();
        pq.pop();
        node *p = new node(l->wei + r->wei, l, r);
        pq.push(p);
    }
    node *root = pq.top();

    while (getline(in, s))
    {
        out << decode(root, s) << endl;
    }
    in.close();
    out.close();
    del(root);
    return 0;
}
