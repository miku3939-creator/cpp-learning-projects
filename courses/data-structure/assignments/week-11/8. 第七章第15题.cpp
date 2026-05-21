/*8. 第七章第15题
【问题描述】

给定一个由n个不相同字符构成的字符串表示的层次遍历序列和另一个由相同的n个字符组成的中序遍历序列，设计并实现一个算法来构造对应的二叉链存储结构。最后输出该二叉树的前序遍历结果。



【输入形式】

第一行包含一个整数 n，表示二叉树的节点数；第二行为层次遍历序列level，第三行为中序遍历序列in，每个字符代表一个结点值。



【输出形式】

对于每一组输入的序列，输出构建后的二叉树前序遍历结果，各测试用例之间以空行分隔。



【样例输入】

7

A B C D E F G

D B E A F C G



【样例输出】

A B D E C F G*/
/*
层次的第一个为根节点
找到根节点之后
找到左右子树对应的字串
然后后递归地建立树*/
#include<iostream>
#include<map>
#include<string>
#include<sstream>
using namespace std;
class node
{
public:
    node *lc;
    node *rc;
    char val;
    node(char v) : lc(nullptr), rc(nullptr), val(v) {}
    node() : lc(nullptr), rc(nullptr) {}
};
string findl(string l,string m){
    string res="";
    for(char e:l){
        if(m.find(e)!=-1)
        res+=e;
    }
    return res;
}
node * build(string l,string m){
if(l.empty()||m.empty())return nullptr;
char rval=l[0];
int pos=m.find(rval);

string ml=m.substr(0,pos);
string mr=m.substr(pos+1);

string ll=findl(l,ml);
string lr=findl(l,mr);

node *p=new node(rval);
p->lc=build(ll,ml);
p->rc=build(lr,mr);
return p;
}
void print(node *p){
    if(p!=nullptr){
        cout<<p->val<<' ';
        print(p->lc);
        print(p->rc);
    }
}
int main(){
int n;
string line,l="",m="";
char e;
cin>>n;
cin.ignore();
getline(cin,line);
stringstream ss(line);
while(ss>>e){
    l.push_back(e);
}
getline(cin,line);
stringstream s(line);
while(s>>e){
    m.push_back(e);
}
node *root=build(l,m);
print(root);
cout<<endl;
return 0;
}