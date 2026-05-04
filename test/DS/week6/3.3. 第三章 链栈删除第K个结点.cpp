#include <iostream>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node() : next(nullptr) {}
    Node(int val) : val(val), next(nullptr) {}
};
class stack
{

public:
    Node *head;
    Node *tail;
    int size;
    stack() : head(new Node)
    {
        size = 0;
        tail = nullptr;
    }
    ~stack()
    {
        Node *p = head, *q;
        while (p != nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
    int top()
    {
        if (size == 0)
            return 0;
        return head->next->val;
    }
    void pop()
    {
        if (size == 0)
            return;
        size--;
        Node *p = head->next;
        head->next = p->next;
        delete p;
    }
    void push(int v)
    {
        if (head->next == nullptr)
        {
            head->next = new Node(v);
            tail = head->next;
            size++;
        }
        else
        {
            tail->next = new Node(v);
            tail = tail->next;
            size++;
        }
    }
    void deletek(int k)
    {
        if (k > size || k <= 0)
        {
            cout << "error" << endl;
            return;
        }
        Node *p = head;
        for (int i = 0; i < k - 1; i++)
        {
            p = p->next;
        }
        Node *q = p->next;
        cout << q->val << endl;
        p->next = q->next;
        delete q;
    }
};
int main()
{
    int n, e;
    stack s;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> e;
        s.push(e);
    }
    cin >> e;
    s.deletek(e);
    for (int i = 0; i < s.size; i++)
    {
        cout << s.top() << ' ';
        s.pop();
    }

    cout << endl;
    return 0;
}