#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    node(char v) : lc(nullptr), rc(nullptr), val(v) {}
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
    node *build(string s)
    {
        stack<node *> st;
        node *p;
        int i = 0;
        bool flag;
        while (i < s.size())
        {
            char c = s[i];
            switch (c)
            {
            case '(':
                st.push(p);
                flag = true;
                break;
            case ')':
                st.pop();
                break;
            case ',':
                flag = false;
                break;
            default:
                p = new node(c);
                if (r == nullptr)
                    r = p;
                else
                {
                    if (flag && !st.empty())
                        st.top()->lc = p;
                    else if (!st.empty())
                        st.top()->rc = p;
                }
                break;
            }
            i++;
        }
    }
    node *build2(string s, int &i)
    {
        if (i >= s.size())
            return nullptr;
        char c = s[i++];
        if (s[i] == '#')
            return nullptr;
        node *p = new node(c);
        p->lc = build2(s, i);
        p->rc = build2(s, i);
    }

    void printp(node *p)
    {
        if (p != nullptr)
        {
            cout << p->val;
            printp(p->lc);
            printp(p->rc);
        }
    }
    void printm(node *p)
    {
        if (p != nullptr)
        {
            printp(p->lc);
            cout << p->val;
            printp(p->rc);
        }
    }
    void printr(node *p)
    {
        if (p != nullptr)
        {
            printp(p->lc);
            printp(p->rc);
            cout << p->val;
        }
    }
    void later(node *r)
    {
        queue<node *> q;
        q.push(r);
        while (!q.empty())
        {
            node *k = q.front();
            cout << k->val << ' ';
            q.pop();
            if (k->lc != nullptr)
                q.push(k->lc);
            if (k->rc != nullptr)
                q.push(k->rc);
        }
    }

    void kcount0(node *p, int h, int k, int &cnt)
    {
        if (p == nullptr)
            return;
        if (h == k)
            cnt++;
        if (h < k)
        {
            kcount0(p->lc, h+1, k, cnt);
            kcount0(p->lc, h+1, k, cnt);
        }
    }

    
    int kcount(int k)
    {
        int cnt=0;
        kcount0(r,0,k,cnt);
        return cnt;
    }

};
int main()
{
    string line;
    tree t;
    getline(cin, line);
    t.build(line);
    t.printp(t.r);
    cout << endl;
    t.printm(t.r);
    cout << endl;
    t.printr(t.r);
    cout << endl;
}