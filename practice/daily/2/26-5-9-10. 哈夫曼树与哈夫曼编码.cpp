#include <iostream>
#include <queue>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char c;
    int freq;
    node(char c, int f) : lc(nullptr), rc(nullptr), c(c), freq(f) {}
    node(int f, node *l, node *r) : lc(l), rc(r), c(127), freq(f) {}
    node() : lc(nullptr), rc(nullptr) {}
};
class mys
{
public:
    bool operator()(node* a, node* b)
    {
        if (a->freq == b->freq)
            return a->c > b->c;
        return a->freq > b->freq;
    }
};

int main()
{
    priority_queue<node *, vector<node *>, mys> q;
    int n, e;
    cin >> n;
    for (char i = 'A'; i < 'A' + n; i++)
    {
        cin >> e;
        q.push(new node(i, e));
    }
    e = 0;
    while (q.size() > 1)
    {
        node *l = q.top();
        q.pop();
        node *r = q.top();
        q.pop();
        node *p = new node(l->freq + r->freq, l, r);
        e += p->freq;
        q.push(p);
    }
    node *root = q.top();
    cout << e << endl;
    return 0;
}