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
    char val;
    node(char v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr), val() {}
};
node *build(vector<char> &v, int &index)
{
    if (index >= v.size())
        return nullptr;
    char val = v[index++];
    if (val == '#')
        return nullptr;
    node *p = new node(val);
    p->lc = build(v, index);
    p->rc = build(v, index);
    return p;
}
bool twin(node *p, node *q)
{
    if (p == nullptr && q == nullptr)
        return true;
    if (p == nullptr || q == nullptr)
        return false;
    if (p->val != q->val)
        return false;
    return twin(p->lc, q->rc) && twin(p->rc, q->lc);
}
int main()
{
    vector<char> v;
    string line;
    char e;
    int i=0;
    getline(cin,line);
    stringstream ss(line);
    while(ss>>e){
        v.push_back(e);
    }
    node *r=build(v,i);
    if(r==nullptr){
        cout<<"Yes"<<endl;
        return 0;
    }
    bool a=twin(r->lc,r->rc);
    if(a)cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    return 0;
}