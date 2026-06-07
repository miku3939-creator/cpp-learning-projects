/*12. 二叉树重建-根据遍历序列
二叉树重建-根据遍历序列
一、问题描述
给定一棵二叉树的先序遍历和中序遍历序列，重建这棵二叉树，并输出后序遍历序列。

二、输入形式
第一行一个数，表示节点个数。
第二行输入若干个整数，表示先序遍历序列。
第三行输入若干个整数，表示中序遍历序列。
两个序列长度相同，节点值互不相同。

三、输出形式
输出后序遍历序列，用空格分隔。

四、样例输入

5 
3 9 20 15 7
9 3 15 20 7
五、样例输出

9 15 7 20 3
六、样例说明
先序：3 9 20 15 7
中序：9 3 15 20 7

重建过程：

先序第一个元素3是根节点

在中序中找到3，左边[9]是左子树，右边[15,20,7]是右子树

递归重建左子树：先序[9]，中序[9]

递归重建右子树：先序[20,15,7]，中序[15,20,7]

后序遍历：9 15 7 20 3

七、评分标准
共10个测试用例。

八、类库使用要求
必须手动实现二叉树结构。*/
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    int val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr) {}
};
node *build(vector<int> &p, int pb, int pe, vector<int> &m, int mb, int me, map<int, int> findex)
{
    if (pb > pe)
        return nullptr;
    if (mb > me)
        return nullptr;
    int rootval = p[pb];
    int mm = findex[rootval];
    int pr = mm - mb ;
    node *root = new node(rootval);
    root->lc = build(p, pb + 1, pb + pr, m, mb , mm-1, findex);
    root->rc = build(p, pb + pr + 1, pe, m, mm+1, me, findex);
    return root;
}
node *buildtree(vector<int> &p, vector<int> &m)
{
    map<int, int> findex;
    for (int i = 0; i < m.size(); i++)
    {
        findex[m[i]] = i;
    }
    return build(p, 0, p.size() - 1, m, 0, m.size() - 1, findex);
}

void print(node *p)
{
    if (p != nullptr)
    {
        print(p->lc);
        print(p->rc);
        cout << p->val << ' ';
    }
}
int main()
{
    int n, e;
    vector<int> p, m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> e;
        p.push_back(e);
    }
    for (int i = 0; i < n; i++)
    {
        cin >> e;
        m.push_back(e);
    }
    node *root = buildtree(p, m);
    print(root);
    return 0;
}