/*17. 判断是否为BST
判断是否为BST
一、问题描述
给定一棵二叉树，判断它是否是二叉搜索树（BST）。

BST的定义：

节点的左子树只包含小于当前节点的数

节点的右子树只包含大于当前节点的数

所有左子树和右子树自身必须也是BST

不存在相等的节点值

二、输入形式
一行若干个整数，表示二叉树的先序遍历序列，空节点用-1表示。

三、输出形式
输出"YES"表示是BST，输出"NO"表示不是BST。

四、样例输入

5 3 2 -1 -1 4 -1 -1 7 6 -1 -1 8 -1 -1
五、样例输出

YES
六、样例说明

    5
   / \
  3   7
 / \ / \
2  4 6  8
满足BST性质。

七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现二叉树结构。*/
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
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
bool bst(node *p, long long &pre)
{
    if (p == nullptr)
        return true;
    if (!bst(p->lc, pre))
        return false;
    if (p->val <= pre)
        return false;
    pre = p->val;
    return bst(p->rc, pre);
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
    long long m=LLONG_MIN;
    bool ok = bst(r,m);
    if (ok)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}