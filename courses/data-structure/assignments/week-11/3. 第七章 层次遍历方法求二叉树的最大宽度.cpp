/*3. 第七章 层次遍历方法求二叉树的最大宽度
【问题描述】


设计一个算法，采用层次遍历方法求给定的二叉树的最大宽度。最大宽度是指在所有层中具有最多节点的层数中的节点数。

【输入形式】

以空格分隔的一系列整数，表示二叉树的前序遍历序列。其中-1表示该位置上的子结点不存在。例如："1 2 -1 -1 3 4 -1 -1 -1"表示一个含有4个节点的非完整二叉树。

【输出形式】

单行输出，返回该二叉树的最大宽度。

【输入样例】

1 2 -1 -1 3 4 -1 -1 -1
【输出样例】

2
【样例说明】

在给定的二叉树中，最宽的一层有两个节点（即第二层），所以返回值为2。

*/
/*
思路：
用队列进行层次遍历
统计最大宽
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    int val;
    int h;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
    node(int v, int h) : lc(nullptr), rc(nullptr), val(v), h(h) {}
};
node *build(vector<int> &v, int &index)
{
    if (index >= v.size())
        return nullptr;
    int val = v[index++];
    if (val == -1)
        return nullptr;
    node *p = new node(val);
    p->lc = build(v, index);
    p->rc = build(v, index);
    return p;
}

int maxw(node *p)
{
    queue<node *> q;
    q.push(p);
    int max = 0;
    while (!q.empty())
    {
        int m = q.size();
        for (int i = 0; i < m; i++)
        {
            node *a = q.front();
            q.pop();
            if (a->lc != nullptr)
                q.push(a->lc);
            if (a->rc != nullptr)
                q.push(a->rc);
        }
        if(m>max) max=m;
    }
    return max;
}
int main()
{
    string line;
    getline(cin,line);
    stringstream ss(line);
    int e, i = 0;
    vector<int> v;
    while (ss >> e)
    {
        v.push_back(e);
    }
    node *r = build(v, i);
    cout<<maxw(r)<<endl;
}