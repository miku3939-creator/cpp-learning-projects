/*2. 极限管道最大通流
问题描述
输水管道网络呈二叉树状，每条管道有最大流量上限（节点值代表该段管道上限）。水流从主泵站（根）向各出水口（叶子）输送。一条通水路线的实际流量等于路径上各段管道的最小值。工程师需要找出流量最大的那条通水路线。

任务
给定管道树，输出从根到任意叶子的路径上，路径最小值的最大可能值。

输入形式
输入由多行组成：

第一行为一个整数 N，表示二叉树中结点的数量。

接下来 N 行，每行描述一个结点的信息，格式为：

父节点值 左孩子值 右孩子值
如果某个孩子为空，则用 # 表示。

第一行即为根节点，格式同样为 父节点值 左孩子值 右孩子值，其中「父节点值」就是根节点自身的值。

输出形式
输出一个整数，表示最大可能的通水流量。

样例输入
5
3 2 4
2 5 #
4 # 6
5 # #
6 # #
样例输出
3
样例说明
树结构如下：

    3
   / \
  2   4
 /     \
5       6
路径 3→2→5 的瓶颈：min(3,2,5) = 2
路径 3→4→6 的瓶颈：min(3,4,6) = 3
最大瓶颈为 3。

评分标准
本题目共 10 个测试用例。

类库使用要求
禁止使用 STL 中的树形结构库（如 std::map 嵌套模拟树）

允许使用标准输入输出库（如 iostream、cstdio 等）

允许使用vector、stack、queue容器库。

需自行实现二叉树的节点结构与遍历逻辑

未按题意进行编码求解，扣减得分的50%*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct node
{
    int v;
    node *lc;
    node *rc;
    node() : lc(nullptr), rc(nullptr) {}
    node(char v) : v(v), lc(nullptr), rc(nullptr) {}
};
node *find(node *p, int v)
{
    if (p == nullptr)
        return nullptr;
    if (p->v == v)
        return p;
    else
    {
        node *l = find(p->lc, v);
        node *r = find(p->rc, v);
        if (l != nullptr)
            return l;
        return r;
    }
}
vector<int> pa;
void fmin(node *p, int min)
{
    if (p == nullptr)
        return;
    if (p->lc == nullptr && p->rc == nullptr)
    {
        if (p->v < min)
            min = p->v;
        pa.push_back(min);
        return;
    }
    else
    {
        if (p->v < min)
            min = p->v;
        fmin(p->lc, min);
        fmin(p->rc, min);
    }
}
int main()
{
    int n;
    cin >> n;
    string t, l, r;
    node *root = nullptr;
    for (int i = 0; i < n; i++)
    {
        cin >> t >> l >> r;
        node *p = new node(stoi(t));

        if (root == nullptr)
        {
            root = p;
            if (l != "#")
                p->lc = new node(stoi(l));
            if (r != "#")
                p->rc = new node(stoi(r));
        }
        else
        {
            node *q = find(root, stoi(t));
            if (l != "#")
                q->lc = new node(stoi(l));
            if (r != "#")
                q->rc = new node(stoi(r));
        }
    }
    fmin(root, 0x3f3f3f3f);
    int max = -1;
    for (int e : pa)
    {
        if (e > max)
            max = e;
    }
    if (max == -1)
        cout << 0 << endl;
    else
        cout << max << endl;
    return 0;
}
