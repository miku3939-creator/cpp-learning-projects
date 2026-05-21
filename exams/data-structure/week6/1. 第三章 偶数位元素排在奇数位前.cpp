#include <iostream>
#include <string>
#include <sstream>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node() : next(nullptr) {}
    Node(int val) : val(val), next(nullptr) {}
};
class queue
{
private:
    Node *head;
    Node *tail;

public:
    int size;
    queue() : head(new Node), tail(nullptr), size(0) {}
    void pushback(int val)
    {
        if (head->next == nullptr)
        {
            head->next = new Node(val);
            tail = head->next;
        }
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }
        size++;
    }
    void popfront()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << head->next->val << ' ';
        Node *temp = head->next;
        head->next = temp->next;
        delete temp;
        size--;
    }
    ~queue()
    {
        Node *p = head, *q;
        while (p != nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};

int main()
{
    string line;
    getline(cin, line);
    bool single = true;
    stringstream ss(line);
    int e;
    queue q1;
    queue q2;
    while (ss >> e)
    {
        if (single == true)
        {
            q1.pushback(e);
            single = false;
        }
        else
        {
            q2.pushback(e);
            single = true;
        }
    }
    while (q2.size != 0)
    {
        q2.popfront();
    }
    while (q1.size != 0)
    {
        q1.popfront();
    }
    cout << endl;
    return 0;
}