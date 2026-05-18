/*
【问题描述】

假设二叉树中的每个结点值为单个字符，采用二叉链存储结构存储。设计一个算法按从右到左的次序输出一棵二叉树bt中的所有叶子结点。


【输入形式】

输入为二叉树的先序遍历序列（带空指针标记），其中空子树用 # 表示，非空结点用单个字符表示。



【输出形式】

从右到左输出所有叶子结点的值，空格分隔；若树为空，则无输出。


【样例输入】

ABD##E##CF###


【样例输出】

F E D


【样例说明】

叶子结点为 D, E, F ，从右到左的次序为 F→E→D


【评分标准】
*/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    node(int v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr) {}
};
node *build(vector<char> &v, int &index)
{
    if (index >= v.size())
        return nullptr;
    char val = v[index++];
    if (val == '#')
        return nullptr;
    node *p = new node(val);
    p->lc = build(v, index);
    p->rc = build(v, index);
    return p;
}
void print(node *p){
    if(p==nullptr)return ;
    if(p->lc==nullptr&&p->rc==nullptr)
        cout<<p->val<<' ';
    print(p->rc);
    print(p->lc);    
    
}
int main()
{
    string line;
    getline(cin,line);
    stringstream ss(line);
    char e;
    int i = 0;
    vector<char> v;
    while (ss >> e)
    {
        v.push_back(e);
    }
    node *r = build(v, i);
    print(r);
}