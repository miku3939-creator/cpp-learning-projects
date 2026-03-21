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
class List
{
public:
    Node *head;
    Node *tail;
    List() : head(NULL), tail(NULL) {}

    void insert(int val)
    {
        if (head == NULL)
        {
            head = new Node(val);
            tail = head;
        }
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
};
int main()
{
    List l1, l2, l3;
    int x;
    while (1)
    {
        cin >> x;
        if (x == -1)
            break;
        l1.insert(x);
    }

    while (1)
    {
        cin >> x;
        if (x == -1)
            break;
        l2.insert(x);
    }
    Node *p = l1.head;
    Node *q = l2.head;
    while (p != NULL && q != NULL)
    {
        if (p->val < q->val)
        {
            l3.insert(p->val);
            p = p->next;
        }
        else
        {
            l3.insert(q->val);
            q = q->next;
        }
    }
    while (p != NULL)
    {
        l3.insert(p->val);
        p = p->next;
    }
    while (q != NULL)
    {
        l3.insert(q->val);
        q = q->next;
    }

    p = l3.head;
    while (p != NULL)
    {
        cout << p->val << ' ';
        p = p->next;
    }
    cout << endl;
    return 0;
}