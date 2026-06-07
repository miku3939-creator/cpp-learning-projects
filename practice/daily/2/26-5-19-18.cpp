/*18. 第k小的元素
第k小的元素
一、问题描述
给定一棵二叉搜索树（BST），找出其中第k小的元素（1 ≤ k ≤ 节点总数）。

二、输入形式
第一行输入一个正整数k（1 ≤ k ≤ 10000）。
第二行输入若干个整数，表示BST的先序遍历序列，空节点用-1表示。

三、输出形式
输出一个整数，表示第k小的元素。

四、样例输入

3
5 3 2 -1 -1 4 -1 -1 6 -1 -1
五、样例输出

4
六、样例说明
BST结构：

    5
   / \
  3   6
 / \
2   4
中序遍历（升序）：2, 3, 4, 5, 6
第3小的元素是4。

七、评分标准
共8个测试用例。

八、类库使用要求
必须手动实现BST结构。*/#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// 手动实现二叉树结构
class node
{
public:
    node *lc;
    node *rc;
    int val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
};

// 引用传递建树，安全且不拷贝大数组
node *build(const vector<int> &v, int &i)
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

// ✨ 核心：中序遍历寻找第 k 小的元素
void kthSmallest(node *p, int k, int &count, int &ans)
{
    // 剪枝：如果已经找到答案，或者节点为空，直接返回
    if (p == nullptr || count >= k)
        return;

    // 1. 递归左子树
    kthSmallest(p->lc, k, count, ans);

    // 2. 处理当前根节点
    count++; // 遇到一个节点，计数器加 1
    if (count == k)
    {
        ans = p->val; // 锁死答案
        return;
    }

    // 3. 递归右子树
    kthSmallest(p->rc, k, count, ans);
}

int main()
{
    // 解除流同步，防止大数据量超时
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    if (!(cin >> k)) return 0;
    
    cin.ignore(); // 吞掉第一行数字后面的换行符，防止 getline 读空

    int e, i = 0;
    vector<int> v;
    string line;
    if (getline(cin, line))
    {
        stringstream ss(line);
        while (ss >> e)
        {
            v.push_back(e);
        }
    }

    node *r = build(v, i);

    int count = 0; // 计数器
    int ans = -1;  // 存储最终答案
    
    kthSmallest(r, k, count, ans);

    cout << ans << "\n";

    return 0;
}