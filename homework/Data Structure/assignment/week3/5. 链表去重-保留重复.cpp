#include <iostream>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node(int val) : val(val), next(NULL) {}
    Node() : next(NULL) {}
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
    ~List()
    {
        Node *p = head, *q;
        while (p != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};
int main()
{
    int val;
    List list;
    while (1)
    {
        cin >> val;
        if (val == -1)
            break;
        list.insert(val);
    }
    Node *slow = list.head;
    Node *fast = list.head;
    while (fast != NULL)
    {
        if (slow->val == fast->val)
            fast = fast->next;
        else
        {
            slow = slow->next;
            slow->val = fast->val;
            fast = fast->next;
        }
    }
    fast = slow->next;
    slow->next=NULL;
    slow=fast;
    while (slow != NULL)
    {
        fast = slow->next;
        delete slow;
        slow = fast;
    }
    slow = list.head;
    while (slow != NULL)
    {
        cout << slow->val << ' ';
        slow = slow->next;
    }
    cout << endl;
    return 0;
}