/*【问题描述】假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。请设计一个算法，采用先序遍历的方法输出二叉树 bt 中所有结点的层次（根结点所在层为 1）。

【输入形式】
第一行输入一个整数 n，表示二叉树的结点数（1 ≤ n ≤ 1000）。

接下来 n 行，每行输入一个结点的信息，格式为：

结点值 左子结点值 右子结点值

【输出形式】

按先序遍历顺序依次输出结点的值及其所在的层次，每个结点占一行，格式如下：

结点值 层次

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

A 1

B 2

D 3

E 3

C 2

F 3

G 4
*/
/*
参考找最小枝长
用数组代替指针存数
用队列进行层次遍历
返回所有节点的值与层
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
    int he;
};
void print(char r,vector<node> &v){
    if(r!='#'){
        cout<<r<<' '<<v[r].he<<endl;
        print(v[r].lc,v);
        print(v[r].rc,v);
    }
}
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
        int y = q.size();
        for (int i = 0; i < y; i++)
        {
            char curr = q.front();
            q.pop();
            v[curr].he=h;
            if (v[curr].lc != '#')
                q.push(v[curr].lc);
            if (v[curr].rc != '#')
                q.push(v[curr].rc);
        }
        h++;
    }
    print(x1,v);
    return 0;
}