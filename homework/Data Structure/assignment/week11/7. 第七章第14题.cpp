/*7. 第七章第14题

【问题描述】

在给定的二叉树结构中，每个结点值为单个字符。设计一个算法，采用先序遍历方法求出某个值为x的结点的所有子孙。



【输入形式】

输入由多行组成：

第一行为一个整数N，表示二叉树中结点的数量。

接下来N行，每行描述一个结点的信息，格式为：父节点值 左孩子值 右孩子值

如果某个孩子为空，则用‘#’表示。

最后一行为目标字符x。

【输出形式】

按先序遍历的顺序输出包含所有目标节点x的子孙结点值。



【样例输入】

6

A B C

B D E

C # F

D # #

E # #

F # #

B



【样例输出】

D E*/
/*
参考找最小枝长
用数组代替指针存数
不可以默认根节点是1
先序遍历直到找到后输出*/
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
void print(vector<node> &v,char r,char x,bool ok){
if(r!='#'){
    if(ok)cout<<r<<' ';
    if(r==x) ok=true;
    print(v,v[r].lc,x,ok);
    print(v,v[r].rc,x,ok);
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
    print(v,x1,x,false);
    return 0;
}