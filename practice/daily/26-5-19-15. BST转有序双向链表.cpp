/*15. BST转有序双向链表
BST转有序双向链表
一、问题描述
给定一棵二叉搜索树（BST），将其转换为一个有序双向链表。要求不能创建新节点，只能调整指针指向。

双向链表要求：

节点值按升序排列

每个节点有prev和next指针

输出链表的头节点和尾节点值

二、输入形式
一行若干个整数，表示BST的先序遍历序列，空节点用-1表示。

三、输出形式
输出一行两个整数，分别表示双向链表的头节点和尾节点值。

四、样例输入

4 2 1 -1 -1 3 -1 -1 5 -1 -1
五、样例输出

1 5
六、样例说明
BST结构：

    4
   / \
  2   5
 / \
1   3
中序遍历：1 2 3 4 5
转换为双向链表：1 ↔ 2 ↔ 3 ↔ 4 ↔ 5
头节点是1，尾节点是5。

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    int val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
};
node *build(vector<int> &v, int &i)
{
    if (i >= v.size())
        return nullptr;
    int val = v[i++];
    if (val == -1)
        return nullptr;
    node *p = new node(val);
    p->lc = build(v, i);
    p->rc = build(v, i);
    return p;
}
node *head_node = nullptr; 
node *pre_node = nullptr;  

void convert(node *curr)
{
    if (curr == nullptr)
        return;

    convert(curr->lc);

    if (pre_node == nullptr)
    {
        head_node = curr;
    }
    else
    {
        pre_node->rc = curr;
        curr->lc = pre_node;
    }
    pre_node = curr;

    convert(curr->rc);
}
node *trans(node *r)
{
    head_node = nullptr;
    pre_node = nullptr;
    convert(r);
    return head_node;
}
void print(node *h)
{
    if (h == nullptr)
        return;

    node *tail = h;
    while (tail->rc != nullptr)
    {
        tail = tail->rc;
    }

    cout << h->val << " " << tail->val << "\n";
}
int main()
{
    int e, i = 0;
    vector<int> v;
    string line;
    getline(cin, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    node *r = build(v, i);
    node *h = trans(r);
    print(h);
}