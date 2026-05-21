#include <iostream>
using namespace std;
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
int main()
{
    int n, e;
    cin >> n;
    stack s(n);
    cqueue c(n + 1);
    bool *data = new bool[n];
    for (int i = 0; i < n; i++)
    {
        cin >> e;
        if (e == -1)
        {
            data[i] = true;
        }
        else
        {
            data[i] = false;
            s.push(e);
        }
    }
    for (int i = 0; i < n; i++)
    {

        if (data[i])
        {
            c.push(-1);
            continue;
        }
        e = s.top();
        s.pop();
        c.push(e);
    }
    while (!c.empty())
    {
        c.pop(e);
        cout << e << ' ';
    }
    cout << endl;
    delete[] data;
    return 0;
}