/*问题描述】

假设一棵二叉树采用二叉链 bt存储，每个结点的值为整数。设计一个算法，输出从根结点到每个叶子结点的路径及其路径和。
路径和是指路径中的所有结点值之和。

叶子结点是指没有左右子结点的结点。

【输入形式】

第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

若左子结点或右子结点为空，则用字符 # 表示。

【输出形式】

每行输出从根结点到每个叶子结点的路径及其路径和，格式如下：

路径: 结点值1 结点值2 ... 结点值n

路径和: path_sum

路径按字典序输出。

路径和为路径中所有结点值的总和。

如果树中没有叶子结点，输出 "No Leaf"。
【样例输入】

6
1 2 3
2 4 5
3 # 6
4 # #
5 # #
6 # #

【样例输出】

路径: 1 2 4

路径和: 7

路径: 1 2 5

路径和: 8

路径: 1 3 6

路径和: 10

【样例说明】
【评分标准】*/
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
struct node
{
    int v;
    node *lc;
    node *rc;
    node *pre;
    node(int v) : v(v), lc(nullptr), rc(nullptr), pre(nullptr) {}
};
vector<int> path;
vector<vector<int>> v;
void DFS(node *r)
{
    if (r->lc == nullptr && r->rc == nullptr)
    {
        v.push_back(path);
        return;
    }

    if (r->lc != nullptr)
    {
        path.push_back(r->lc->v);
        DFS(r->lc);
        path.pop_back();
    }
    if (r->rc != nullptr)
    {
        path.push_back(r->rc->v);
        DFS(r->rc);
        path.pop_back();
    }
}
int main()
{
    int n, u;
    string l, r;
    map<int, node *> m;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> u >> l >> r;
        if (m.find(u) == m.end())
        {
            m[u] = new node(u);
        }
        if (l != "#")
        {

            int ll = stoi(l);
            if (m.find(ll) == m.end())
            {
                m[ll] = new node(ll);
            }
            m[u]->lc = m[ll];
            m[ll]->pre = m[u];
        }
        if (r != "#")
        {

            int rr = stoi(r);
            if (m.find(rr) == m.end())
            {
                m[rr] = new node(rr);
            }
            m[u]->rc = m[rr];
            m[rr]->pre = m[u];
        }
    }
    node *root = nullptr;

    for (auto it : m)
    {

        if (it.second->pre == nullptr)
        {
            root = it.second;
            break;
        }
    }
    path.push_back(root->v);
    DFS(root);
    if (v.empty())
    {
        cout << "No Leaf" << endl;
        return 0;
    }
    sort(v.begin(), v.end());
    for (auto s : v)
    {
        int cnt = 0;
        cout << "路径: ";
        for (int e : s)
        {
            cout << e << ' ';
            cnt += e;
        }
        cout << endl;
        cout << "路径和: " << cnt << endl;
    }
    return 0;
}
