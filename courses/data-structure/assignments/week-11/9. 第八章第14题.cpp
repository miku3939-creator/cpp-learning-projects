/*9. 第八章第14题
【问题描述】

假设一棵哈夫曼树采用二叉链 bt 存储，结点类型如下：

struct BTNode {
    char ch;       // 编码的字符或者为空
    int data;      // 权值
    BTNode* lchild;
    BTNode* rchild;};
设计一个算法，输出每个叶子结点对应字符的哈夫曼编码。哈夫曼编码是从根节点到叶子节点的路径，左分支为 0，右分支为 1。


【输入形式】

第一行包含一个整数N（1 <= N <= 20），表示字符的数量。接下来N行每行包含两个部分，第一个是一个字符，第二个是该字符对应的权值，用空格分隔。



【输出形式】

对于每个叶子结点的字符，按照输入的顺序，输出其哈夫曼编码，以空格分隔。

【样例输入】

4

a 5

b 9

c 12

d 13


【样例输出】

00 01 10 11


【样例说明】

对于给定的字符及其权值，构建哈夫曼树后，得到每个叶子结点对应的编码为：a -> 00, b -> 01, c -> 10, d -> 11。*/
#include <iostream>
#include <map>
#include <string>
#include <queue>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    int f;
    node(char v, int f) : lc(nullptr), rc(nullptr), val(v), f(f) {}
    node() : lc(nullptr), rc(nullptr) {}
};
class mys
{
public:
    bool operator()(node *a, node *b)
    {
        if (a->f != b->f)
            return a->f > b->f;
        return a->val > b->val;
    }
};

void encode(node *r, string code, map<char, string> &m)
{
    if (r != nullptr)
    {
        if (r->lc == nullptr && r->rc == nullptr)
        {
            m[r->val] = code;
            return;
        }
        encode(r->lc, code + '0', m);
        encode(r->rc, code + '1', m);
    }
}
int main()
{
    int n, f;
    char ch;
    priority_queue<node *, vector<node *>, mys> p;
    cin >> n;
    vector<char> v;
    for (int i = 0; i < n; i++)
    {
        cin >> ch >> f;
        v.push_back(ch);
        p.push(new node(ch, f));
    }
    while (p.size() > 1)
    {
        node *l = p.top();
        p.pop();
        node *r = p.top();
        p.pop();
        node *q = new node(127, l->f + r->f);
        q->lc = l;
        q->rc = r;
        p.push(q);
    }
    node *root = p.top();
    map<char, string> m;
    encode(root, "", m);
    for (int i = 0; i < v.size(); i++)
    {
        cout << m[v[i]] << ' ';
    }
    cout << endl;
    return 0;
}