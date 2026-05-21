/*问题描述】

给定一个不含重复元素的整数数组，一个以此数组构建的最大二叉树定义如下：

① 二叉树的根是数组中的最大元素。

② 左子树是通过数组中最大值左边部分构造出的最大二叉树。

③ 右子树是通过数组中最大值右边部分构造出的最大二叉树。

      要求通过给定的数组构建最大二叉树，并且用括号表示法输出构建好的最大二叉树，假设给定的数组的大小在[1,1000]之间。

【输入形式】

     在一行中输入整数数组，用空格分隔开
【输出形式】

    输出生成的二叉树的树根节点的值。
【样例输入】

3 2 1 6 0 5

【样例输出】

6(3(,2(,1)),5(0))

【样例说明】

     测试数据的文件名为in.txt

【评分标准】

    该题目有10个测试用例，每通过一个测试用例，得10分。

*/
/*思路：
找出最大值所在位置
然后递归地构建左右子树
*/
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
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

node *build(vector<int> &v, int l, int r)
{
    if (l >= r)
        return nullptr;
    int max = l;
    for (int i = l + 1; i < r; i++)
    {
        if (v[i] > v[max])
            max = i;
    }
    node *p = new node(v[max]);
    p->lc = build(v, l, max);
    p->rc = build(v, max + 1, r);
    return p;
}

void print(node *p)
{
    if (p != nullptr)
    {
        cout << p->val;
        if (p->lc != nullptr || p->rc != nullptr)
        {
            cout << '(';
            print(p->lc);
            if (p->rc != nullptr)
            {
                cout << ',';
                print(p->rc);
            }
            cout << ')';
        }
    }
}
void del(node *p)
{
    if (p != nullptr)
    {
        del(p->lc);
        del(p->rc);
        delete p;
    }
}
int main()
{
    ifstream in("in.txt");
    string line;
    int e;
    vector<int> v;
    getline(in, line);
    stringstream ss(line);
    while (ss >> e)
    {
        v.push_back(e);
    }
    e = v.size();
    node *root = build(v, 0, e);
    print(root);
    del(root);
    return 0;
}