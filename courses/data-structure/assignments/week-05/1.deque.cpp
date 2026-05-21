#include <iostream>
#include <string>
using namespace std;
class Node
{
public:
    int val;
    Node *next;
    Node() : next(nullptr) {}
    Node(int val) : val(val), next(nullptr) {}
};
class dequeNode
{
private:
    Node *head;
    Node *tail;

public:
    int size;
    dequeNode() : head(new Node), tail(nullptr), size(0) {}
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
    void pushfront(int val)
    {
        if (head->next == nullptr)
        {
            head->next = new Node(val);
            tail = head->next;
        }
        else
        {
            Node *temp = head->next;
            head->next = new Node(val);
            head->next->next = temp;
        }
        size++;
    }
    void front()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << head->next->val << endl;
    }
    void back()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << tail->val << endl;
    }
    void popfront()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << head->next->val << endl;
        Node *temp = head->next;
        head->next = temp->next;
        delete temp;
        size--;
    }
    void popback()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
        cout << tail->val << endl;
        Node *temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;
        temp->next = nullptr;
        delete tail;
        tail = temp;
        size--;
    }
};
int main()
{
    int n, e;
    string command;
    dequeNode test;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> command;
        if (command == "PUSH_BACK")
        {
            cin >> e;
            test.pushback(e);
        }
        else if (command == "PUSH_FRONT")
        {
            cin >> e;
            test.pushfront(e);
        }
        else if (command == "FRONT")
        {
            test.front();
        }
        else if (command == "BACK")
        {
            test.back();
        }
        else if (command == "POP_FRONT")
        {
            test.popfront();
        }
        else if (command == "POP_BACK")
        {
            test.popback();
        }
        else if (command == "SIZE")
        {
            cout << test.size << endl;
        }
        else
        {
            break;
        }
    }
    return 0;
}