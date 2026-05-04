#include <iostream>
using namespace std;

class Node
{
public:
    int val;
    Node *next;
    Node() : next(NULL) {}
    Node(int val) : val(val), next(NULL) {}
};
class queue
{
public:
    Node *head;
    queue() : head(new Node) {}

    void insert(int val)
    {
        if (head->next == NULL)
        {
            head->next = new Node(val);
        }
        else
        {
            Node *p = head, *q;
            while (p->next!=NULL&&val > p->next->val)
                p = p->next;
            q = p->next;
            p->next = new Node(val);
            p->next->next = q;
        }
    }
    void popmin()
    {
        if (head->next == NULL)
            return;
        Node *p = head->next;
        head->next = p->next;
        delete p;
    }
    void outmin()
    {
        if (head->next == NULL)
            return;
        cout << head->next->val<<endl;
        return;
    }
    ~queue()
    {
        Node *p = head, *q;
        while (p!= NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};
int main()
{
    int n, op, val;
    queue q;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> val;
            q.insert(val);
            break;
        case 2:
            q.outmin();
            break;
        case 3:
            q.popmin();
            break;
        };
    }
    return 0;
}