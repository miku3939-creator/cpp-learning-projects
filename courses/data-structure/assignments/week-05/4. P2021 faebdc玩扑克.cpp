/*题目描述
zky 有 n 个扑克牌，编号从 1 到 n，zky 把它排成一个序列，每次把最上方的扑克牌放在牌堆底，然后把下一张扑克牌拿出来输出，最终输出的序列恰好是从 1 到 n，faebdc 问你原序列是什么，因为 faebdc 神犇早已在 O(1) 的时间得出结果，如果你在 1 s 内答不出来，faebdc 会吃了你。

输入格式
一个整数 n，表示扑克数目。

输出格式
n 个数，表示扑克序列。

输入输出样例*/
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
    int n;
    cin >> n;
    deque q;
    q.pushback(n);
    for (int i = n - 1; i >= 1; i--)
    {
        q.pushfront(i);
        int e = q.back();
        q.popback();
        q.pushfront(e);
    }
    q.print();
    return 0;
}