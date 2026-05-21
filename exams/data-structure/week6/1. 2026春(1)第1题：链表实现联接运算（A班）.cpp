/*1. 2026春(1)第1题：链表实现联接运算（A班）
【问题描述】

给定两个存储整数（或字母）的二维表R（m₁行n₁列）和S（m₂行n₂列），基于单向链表实现二者的大于连接运算：

（1）大于连接规则：C=R⋈i>jS（R的第i列与S的第j列）；

（2）运算逻辑：先求R和S的笛卡尔积，再筛选出“R的第i列值>S的第j列值”的所有元组，最终结果构成二维表C。

【实验要求】

（1）数据存储：必须采用单向链表存储二维表的行/列数据（如每行数据为一个链表结点，一张表对应链表所有结点）。

（2）运算实现：大于连接的核心逻辑（笛卡尔积生成、大于筛选）需基于链表操作完成，禁止使用数组/容器等替代。

（3）结果要求：输出的结果表C需保留符合条件的所有元组，无冗余数据，行数≤m₁×m₂。

【输入格式】 in.txt文件输入多组数据（文件非空）

第一行测试用例个数k, 第二行：第一个样例数据类型（int或者char）。第三行：两个整数m? 、n?，空格分隔，表示二维表R的行数和列数。

接下来m?行：每行n?个（或字母）整数，空格分隔，表示R的每行数据。 随后一行：两个整数m? 、 n? ，空格分隔，表示二维表S的行数和列。接下来m?行：每行n?个整数（或字母），空格分隔，表示S的每行数据。再一行：两个正整数i、j，空格分隔，表示大于连接的列号（i为R的列号，j为S的列号，列号从1开始计数）。重复K个测试用例。

保证有K个样例，每个二维表类型正确后续正确，但是不保证联接列号符合要求。

【样例输入】文件in.txt内容：

 4

char

3 2

a b

c b

e c

2 2

x y

b h

2 1

int

3 3

1 2 3

2 3 6

4 5 7

2 4

3 6 9 7

5 7 8 6

3 2

int

3 3

1 2 4

3 4 3

20 45 12

2 2

10 20

30 40

1 5

float

3 4

【输出格式】输出到文件out.txt

输出in.txt文件中大于联接运算结果表的所有元组，格式要求：

（1）每行包含n₁+n₂个整数（或字母），空格分隔（为R的一行数据拼接S的一行数据）。

（2）行顺序与笛卡尔积筛选结果一致，行数≤m₁×m₂（无符合条件的元组时无输出）。

（3）每个样例结果之间空一行。

【样例输出】

 对于上述in.txt输入，输出out.txt ：

第1个char样例:

e c b h



第2个int样例:

4 5 7 3 6 9 7



第3个int样例:

列号超出范围!



第4个float样例:

未知的数据类型: float

【评分标准】

要使用链表实现，否则不能得分。*/
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
template <class T>
class Node
{
public:
    vector<T> val;
    Node<T> *next;
    Node() : next(nullptr) {}
    Node(vector<T> val) : val(val), next(nullptr) {}
};
template <class T>
class list
{
public:
    Node<T> *head;
    Node<T> *tail;
    list() : head(new Node<T>), tail(nullptr) {}
    void insert(vector<T> val)
    {
        if (head->next == nullptr)
        {
            head->next = new Node<T>(val);
            tail = head->next;
        }
        else
        {
            tail->next = new Node<T>(val);
            tail = tail->next;
        }
    }
    ~list()
    {
        Node<T> *p = head, *q;
        while (p != nullptr)
        {
            q = p->next;
            delete p;
            p = q;
        }
    }
};
template <class T>
void connect(list<T> &l1, list<T> &l2, ofstream &out, int i, int j)
{
    Node<T> *p = l1.head;
    T a, b;
    while (p->next != nullptr)
    {
        Node<T> *q = l2.head;
        p = p->next;
        a = p->val[i - 1];
        while (q->next != nullptr)
        {
            q = q->next;
            b = q->val[j - 1];
            if (a > b)
            {
                for (int k = 0; k < p->val.size(); k++)
                {
                    out << p->val[k] << ' ';
                }
                for (int k = 0; k < q->val.size(); k++)
                {
                    out << q->val[k] << ' ';
                }
                out << endl;
            }
        }
    }
}
int main()
{
    int n, x, y, y1, y2;
    string t;
    ifstream in("in.txt");
    ofstream out("out.txt");
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> t;

        if (t == "int")
        {
            int e;
            list<int> l1, l2;
            in >> x >> y1;
            for (int k = 0; k < x; k++)
            {
                vector<int> v;
                for (int j = 0; j < y1; j++)
                {
                    in >> e;
                    v.push_back(e);
                }
                l1.insert(v);
            }
            in >> x >> y2;
            for (int k = 0; k < x; k++)
            {
                vector<int> v;
                for (int j = 0; j < y2; j++)
                {
                    in >> e;
                    v.push_back(e);
                }
                l2.insert(v);
            }
            out << "第" << i + 1 << "个int样例:" << endl;
            in >> x >> y;
            if (x > y1 || y > y2)
            {
                out << "列号超出范围!" << endl;
                continue;
            }

            connect(l1, l2, out, x, y);
            out << endl;
        }
        else if (t == "char")
        {
            char e;
            list<char> l1, l2;
            in >> x >> y1;
            for (int k = 0; k < x; k++)
            {
                vector<char> v;
                for (int j = 0; j < y1; j++)
                {
                    in >> e;
                    v.push_back(e);
                }
                l1.insert(v);
            }
            in >> x >> y2;
            for (int k = 0; k < x; k++)
            {
                vector<char> v;
                for (int j = 0; j < y2; j++)
                {
                    in >> e;
                    v.push_back(e);
                }
                l2.insert(v);
            }
            out << "第" << i + 1 << "个char样例:" << endl;
            in >> x >> y;
            if (x > y1 || y > y2)
            {
                out << "列号超出范围!" << endl;
                continue;
            }

            connect(l1, l2, out, x, y);
            out << endl;
        }
        else
        {
            out << "第" << i + 1 << "个" << t << "样例:" << endl;
            out << "未知的数据类型:" << t ;
            continue;
        }
    }
}