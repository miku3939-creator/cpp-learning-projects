#include <iostream>
using namespace std;
class node
{
public:
    int val;
    node *next;
    node(int val) : val(val), next(NULL) {}
    node() : next(NULL) {}
};
class list
{
public:
    node *head;
    node *tail;
    list() : head(NULL), tail(NULL) {}
    void insert(int val)
    {
        if (head == NULL)
        {
            head = new node(val);
            tail = head;
        }
        else
        {
            tail->next = new node(val);
            tail = tail->next;
        }
    }
    ~list(){
        node *p=head,*q;
        while(p!=nullptr){
        q=p->next;
        delete p;
        p=q;
        }
    }
};
node *dex(node *p, int x)
{
    if (p == nullptr)
    {
        return p;
    }
    if (p->val == x)
    {
        node *temp = p->next;
        delete p;
        return temp;
    }
    p->next = dex(p->next, x);
    return p;
}
int main()
{
    int n, val, x;
    list l;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        l.insert(val);
    }
    cin >> x;
    dex(l.head, x);
    node *p = l.head;
    if (p == NULL)
    {
        cout << "NULL" << endl;
    }
    while (p != NULL)
    {
        cout << p->val << ' ';
        p = p->next;
    }
    cout<<endl;
    return 0;
}