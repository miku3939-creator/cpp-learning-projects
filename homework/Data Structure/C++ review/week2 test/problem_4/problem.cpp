/*题4_string拼接与子串

【题目描述】
给定两个字符串 a 和 b，请先将它们拼接成 c=a+b，再输出：
1. 拼接后的字符串 c
2. c 的前 3 个字符（若长度不足 3，则输出整个 c）

【输入格式】
共 6 组测试，每组一行，包含两个不含空格的字符串 a 和 b。

【输出格式】
对于每组测试，输出两行：
第一行输出拼接结果 c
第二行输出 c 的前 3 个字符（或整个 c）

【提示】
可以使用：
string c = a + b;
c.substr(0, 3)*/
#include<iostream>
#include<string>
using namespace std;
int main(){
    string a,b;
    cin>>a>>b;
    string c=a+b;
    cout<<c<<endl;
    cout<<c.substr(0,3)<<endl;
    return 0;
}