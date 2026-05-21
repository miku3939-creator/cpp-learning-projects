#include <iostream>
using namespace std;
class stack
{
    int maxsize;
    int *data;
    int topIndex;

public:
    stack(int m) : maxsize(m),topIndex(-1)
    {
        data = new int(maxsize);
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
    }
    void push(int v)
    {
        data[++topIndex] = v;
    }
};

class cqueue
{
    int maxsize;
    int *data;
    int head, rear;

public:
    cqueue(int m) : maxsize(m)
    {
        data = new int(maxsize);
        head = rear = -1;
    }
    ~cqueue()
    {
        delete[] data;
    }
    int front()
    {
        if (rear == head)
            return 0;
        return data[(head + 1) % maxsize];
    }
    void pop()
    {
        if (rear == head)
            return;
        head = (head + 1) % maxsize;
    }
    void push(int v)
    {
        rear = (rear + 1) % maxsize;
        data[rear] = v;
    }
};
int main()
{
    int n, e;
    cin>>n;
    stack s(n);
    cqueue c(n);
    for (int i = 0; i < n; i++)
    {
        cin >> e;
        s.push(e);
    }
    for (int i = 0; i < n; i++)
    {

        c.push(s.top());
        s.pop();
    }
    for (int i = 0; i < n; i++)
    {
        cout << c.front() << ' ';
        c.pop();
    }
    cout<<endl;
    return 0;
}