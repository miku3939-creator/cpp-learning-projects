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
    Node *first;
    List() : first(NULL) {}

    void createList(int n)
    {
        first = new Node(1);
        Node *p = first;
        for (int i = 2; i <= n; i++)
        {
            p->next = new Node(i);
            p = p->next;
        }
        p->next = first;
    }

    void circle(int n, int m)
    {
        Node *p = first;
        for (int i = 0; i < n; i++)
        {
            int j = 1;
            while (j != m)
            {
                p = p->next;
                j++;
            }
            cout << p->val << ' ';
            Node *q = p->next;
            p->val = q->val;
            p->next = q->next;
            delete q;
        }
        cout << endl;
    }
};
int main()
{
    int n, m;
    cin >> n >> m;
    List list;
    list.createList(n);
    list.circle(n, m);
    return 0;
}