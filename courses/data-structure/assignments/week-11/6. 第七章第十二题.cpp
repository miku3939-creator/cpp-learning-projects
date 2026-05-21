/*【问题描述】假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。请设计一个算法，采用先序遍历的方法计算二叉树 bt 的宽度（即具有最多结点的层的结点数）。

【输入形式】

第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

若左子结点或右子结点为空，则用字符 # 表示。

【输出形式】

输出一个整数，表示二叉树的最大宽度（即具有最多结点的层的结点数）。

【样例输入】

7

A B C

B D E

C # F

D # #

E # #

F G #

G # #

【样例输出】

3
*/
/*
参考找最小枝长
用数组代替指针存数
用队列进行层次遍历
记录层宽，有更大的进行替换；
不可以默认根节点是1*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class node
{
public:
    char lc;
    char rc;
};
int main()
{
    int n;
    char x1, x, l, r;
    cin >> n;
    vector<node> v(256);
    cin >> x1 >> l >> r;
    v[x1].lc = l;
    v[x1].rc = r;
    for (int i = 2; i <= n; i++)
    {
        cin >> x >> l >> r;
        v[x].lc = l;
        v[x].rc = r;
    }
    cin >> x;
    queue<char> q;
    q.push(x1);
    int w= 0;
    while (!q.empty())
    {
        int y= q.size();
        for (int i = 0; i < y; i++)
        {
            char curr = q.front();
            q.pop();
            if (v[curr].lc != '#')
                q.push(v[curr].lc);
            if (v[curr].rc != '#')
                q.push(v[curr].rc);
        }
        if(y>w)w=y;
    }
    cout<<w<<endl;
    return 0;
}