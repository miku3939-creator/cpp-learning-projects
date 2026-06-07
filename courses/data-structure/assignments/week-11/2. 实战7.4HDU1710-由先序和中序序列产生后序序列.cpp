/*【问题描述】

     由二叉树的先序序列和中序序列构造二叉树并求其后序序列
【输入形式】

    每个测试用例的第一行包含一个整数n（1<=n<=1000）表示二叉树的节点个数，所有节点的编号为1~n，后面两行分别给出先序序列和中序序列。可以假设构造出的二叉树是唯一的。
【输出形式】

    对于每个测试用例，输出一行表示其后序序列。
【样例输入】

  9

  1 2 4 7 3 5 8 9 6

  4 7 2 1 8 5 9 3 6

【样例输出】

 7 4 2 8 9 5 6 3 1
【样例说明】
     测试数据的文件名为in.txt*/
/*
思路：
先序遍历的第一个节点是根节点
找到根节点在中序遍历中的位置（用map速查
递归地构建左右子树（考虑始末位置
考虑结束条件
*/
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
    int pr = mm - mb;
    node *root = new node(rootval);
    root->lc = build(p, pb + 1, pb + pr, m, mb, mm - 1, findex);
    root->rc = build(p, pb + pr + 1, pe, m, mm + 1, me, findex);
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
/*int main()
{
    ifstream in("in.txt");
    int n, e;
    vector<int> p, m;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> e;
        p.push_back(e);
    }
    for (int i = 0; i < n; i++)
    {
        in >> e;
        m.push_back(e);
    }
    node *root = buildtree(p, m);
    print(root);
    return 0;
}*/
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
