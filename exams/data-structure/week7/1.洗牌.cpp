#include <iostream>
using namespace std;
class queue
{
public:
    int *data;
    int fro, rear;
    int maxsize;
    queue(int maxsize) : maxsize(maxsize)
    {
        data = new int[maxsize];
        fro = rear = 0;
    }
    ~queue()
    {
        delete[] data;
    }
    bool isempty()
    {
        return (fro == rear);
    }
    bool enqueue(int e)
    {
        if ((rear + 1) % maxsize == fro)
            return false;
        rear = (rear + 1) % maxsize;
        data[rear] = e;
        return true;
    }
    bool dequeue()
    {
        if (fro == rear)
            return false;
        fro = (fro + 1) % maxsize;
        return true;
    }
    int front()
    {
        if (fro == rear)
            return 0;
        int head = (fro + 1) % maxsize;
        return data[head];
    }
    int size()
    {
        return (rear - fro + maxsize) % maxsize;
    }
};
int main()
{
    int n, n2;
    cin >> n;
    if (n % 2 == 0)
    {
        n2 = n / 2;
    }
    else
    {
        n2 = n / 2 + 1;
    }

    queue q1(n+2), q2(n / 2 + 1);
    for (int i = 0; i < n2; i++)
    {
        q1.enqueue(i + 1);
    }
    for (int i = n2; i < n; i++)
    {
        q2.enqueue(i + 1);
    }

    while (!q2.isempty())
    {
        q1.enqueue(q1.front());
        q1.dequeue();
        q1.enqueue(q2.front());
        q2.dequeue();
    }
    if (n % 2 != 0)
    {
        q1.enqueue(q1.front());
        q1.dequeue();
    }
    while (!q1.isempty())
    {
        cout << q1.front() << ' ';
        q1.dequeue();
    }
    cout << endl;
    return 0;
}
