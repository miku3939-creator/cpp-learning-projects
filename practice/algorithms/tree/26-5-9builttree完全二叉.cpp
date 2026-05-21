#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr) {}
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
 
        
};
int main()
{
    int e, i = 0;
    string line;
    vector<int> v;
    tree t;
    getline(cin, line);
    stringstream ss(line);
    while(ss>>e){
        v.push_back(e);
    }
}