#include <iostream>
#include <string>
#include <stack>
using namespace std;
struct node
{
    char v;
    node *lc;
    node *rc;
    node() : lc(nullptr), rc(nullptr) {}
    node(char v) : v(v), lc(nullptr), rc(nullptr) {}
};
void printr(node *p)
{
    if (p == nullptr)
        return;
    printr(p->lc);
    printr(p->rc);
    cout << p->v;
}
int main()
{

    string line;
    getline(cin, line);
    node *r = nullptr;
    int i = 0;
    int n = line.size();
    bool l = false;
    node *p = nullptr;
    stack<node *> s;
    while (i < n)
    {
        char ch = line[i];
        switch (ch)
        {
        case '(':
            s.push(p);
            l = true;
            break;

        case ',':
            l = false;
            break;
        case ')':
            s.pop();
            break;
        default:
            p = new node(ch);
            if (r == nullptr)
                r = p;
            else
            {
                if (l && !s.empty())
                    s.top()->lc = p;
                else if (!s.empty())
                    s.top()->rc = p;
            }
            break;
        };
        i++;
    }
    printr(r);
    cout << endl;
    return 0;
}
