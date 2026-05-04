#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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
    List() : head(new Node), tail(NULL) {}

    void insert(int val)
    {
        if (head ->next== NULL)
        {
            head->next = new Node(val);
            tail = head->next;
        }
        else
        {
            tail->next = new Node(val);
            tail = tail->next;
        }
    }
};
class cqueue
{
public:
    int *data;
    int front, rear;
    int maxsize;
    cqueue(int maxsize) : maxsize(maxsize)
    {
        data = new int[maxsize];
        front = rear = 0;
    }
    ~cqueue()
    {
        delete[] data;
    }
    bool empty()
    {
        return (front == rear);
    }
    bool push(int e)
    {
        if ((rear + 1) % maxsize == front)
            return false;
        rear = (rear + 1) % maxsize;
        data[rear] = e;
        return true;
    }
    bool pop(int &e)
    {
        if (front == rear)
            return false;
        front = (front + 1) % maxsize;
        e = data[front];
        return true;
    }
    bool gethead(int &e)
    {
        if (front == rear)
            return false;
        int head = (front + 1) % maxsize;
        e = data[head];
        return true;
    }
    int getlength()
    {
        return (rear - front + maxsize) % maxsize;
    }
};
class stack
{
public:
    int maxsize;
    int *data;
    int topIndex;
    int size;

    stack(int m) : maxsize(m), topIndex(-1), size(0)
    {
        data = new int[maxsize];
    }
    ~stack()
    {
        delete[] data;
    }
    int top()
    {
        if (topIndex == -1)
            return 0;
        return data[topIndex];
    }
    void pop()
    {
        if (topIndex == -1)
            return;
        topIndex--;
        size--;
    }
    void push(int v)
    {
        data[++topIndex] = v;
        size++;
    }
};
class Node
{
public:
    int val;
    Node *next;
    Node() : next(nullptr) {}
    Node(int val) : val(val), next(nullptr) {}
};
class deque
{
private:
    Node *head;
    Node *tail;

public:
    int size;
    deque() : head(new Node), tail(nullptr), size(0) {}
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
    int front()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return 0;
        }
        return head->next->val;
    }
    int back()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return 0;
        }
        return tail->val;
    }
    void popfront()
    {
        if (head->next == nullptr)
        {
            cout << "EMPTY" << endl;
            return;
        }
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
        Node *temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;
        temp->next = nullptr;
        delete tail;
        tail = temp;
        size--;
    }
    void print()
    {
        Node *p = head;
        while (p->next != NULL)
        {
            p = p->next;
            cout << p->val << ' ';
        }
        cout << endl;
    }
    ~deque()
    {
        Node *p = head, *q;
        while (p->next != NULL)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};
int main()
{
    ifstream in("in.txt");
}
