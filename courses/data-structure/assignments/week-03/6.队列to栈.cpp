#include <iostream>
#include <queue>
#include<string>
using namespace std;

class MyStack
{
private:
    queue<int> q;

public:
    MyStack() {}

    void push(int x)
    {
        int n = q.size();
        q.push(x);
        while (n != 0)
        {
            q.push(q.front());
            q.pop();
            n--;
        }
        cout << "null" << endl;
    }

    void pop()
    {
        if (q.empty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        cout << q.front() << endl;
        q.pop();
    }

    int top()
    {
        if (q.empty())
        {
            cout << "Stack is empty" << endl;
            return;
        }
        cout<<q.front()<<endl;
        return q.front();
    }

    bool empty()
    {if(q.empty())
        cout<<"true"<<endl;
        else cout<<"false"<<endl;
        return q.empty();
    }

    void print()
    {
        if (q.empty())
        {
            cout << "Stack is empty" << endl;
            return;
        }

        queue<int> temp = q;
        while (!temp.empty())
        {
            cout << temp.front() << " ";
            temp.pop();
        }
        cout << endl;
    }
};

int main()
{
    MyStack stack;
    string command;

    while (getline(cin, command))
    {
        if (command == "exit")
        {
            break;
        }
        else if (command.substr(0, 4) == "push")
        {
            int num = stoi((command.substr(5)));
            stack.push(num);
        }
        else if (command == "pop")
        {
            stack.pop();
        }
        else if (command == "top")
        {
            stack.top();
        }
        else if (command == "empty")
        {
            stack.empty();
        }
        else if (command == "print")
        {
            stack.print();
        }
        else
        {
            cout << "未知命令" << endl;
        }
    }

    return 0;
}