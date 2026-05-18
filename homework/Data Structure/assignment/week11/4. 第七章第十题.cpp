/*【问题描述】假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。二叉树 bt 可能有多个值为 x 的结点，每个这样的结点对应一个层次（根结点为第 1 层）。请设计一个算法，求值为 x 的结点所在的最小层次。

【输入形式】

第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

若左子结点或右子结点为空，则用字符 # 表示。

最后一行输入一个字符 x，表示要查找的目标结点值。

【输出形式】

若左子结点或右子结点为空，则用字符 # 表示。

最后一行输入一个字符 x，表示要查找的目标结点值。

【样例输入】

7

A B C

B D E

C # F

D # #

E # #

F G #

G # #

E

【样例输出】

3
*/
/*
参考找最小枝长
用数组代替指针存数
用队列进行层次遍历
找到目标结点就返回最层数
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
    int h = 1;
    while (!q.empty())
    {
        int y= q.size();
        for (int i = 0; i < y; i++)
        {
            char curr = q.front();
            q.pop();
            if (curr== x)
            {
                cout << h << endl;
                return 0;
            }
            if (v[curr].lc != '#')
                q.push(v[curr].lc);
            if (v[curr].rc != '#')
                q.push(v[curr].rc);
        }
        h++;
    }
    cout<<-1<<endl;
    return 0;
}