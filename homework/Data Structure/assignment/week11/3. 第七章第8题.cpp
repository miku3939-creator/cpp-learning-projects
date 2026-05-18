/*3. 第七章第8题
【问题描述】

给出一棵二叉树，采用二叉链存储结构存储，设计一个算法求二叉树的最小枝长，所谓最小枝长，是指根结点到最近叶子结点的路径长度

【输入形式】

第一行一个正整数n

接下来n行，每行三个正整数x,l,r，表示结点x的左右子结点，空节点用0表示

【输出形式】

输出一行一个正整数，表示最小枝长

【样例输入】

3

1 2 0

2 3 0

3 0 0



【样例输出】

2

【样例说明】
【评分标准】

n<=100000*/
/*
用数组代替指针存数
用队列进行层次遍历
找到空结点就返回最小枝长
不可以默认根节点是1*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;
class node
{
public:
    int lc;
    int rc;
};
int main()
{
    int n, x1, x, l, r;
    cin >> n;
    vector<node> v(n + 1);
    cin >> x1 >> l >> r;
    v[x1].lc = l;
    v[x1].rc = r;
    for (int i = 2; i <= n; i++)
    {
        cin >> x >> l >> r;
        v[x].lc = l;
        v[x].rc = r;
    }

    queue<node> q;
    q.push(v[x1]);
    int h = 0;
    while (!q.empty())
    {
        int x = q.size();
        for (int i = 0; i < x; i++)
        {
            node curr = q.front();
            q.pop();
            if (curr.lc == 0 && curr.rc == 0)
            {
                cout << h << endl;
                return 0;
            }
            if (curr.lc != 0)
                q.push(v[curr.lc]);
            if (curr.rc != 0)
                q.push(v[curr.rc]);
        }
        h++;
    }
    return 0;
}