/*题8_模板类与string结合_字典序较大值

【题目描述】
定义一个类模板 Compare<T>，保存两个值 a 和 b，并提供成员函数 bigger()，返回其中较大的那个值。
本题中输入的是两个字符串，要求输出字典序较大的字符串。
若两个字符串相同，输出任意一个即可。

【输入格式】
共 6 组测试，每组一行，包含两个不含空格的字符串。

【输出格式】
对于每组测试，输出字典序较大的字符串。

【提示】
字符串可以直接使用 > 比较大小，这比较的是字典序。
例如：
"banana" > "apple" 为真*/
#include<iostream>
using namespace std;
template <class T>
class Compare
{
    public:
    T a;
    T b;
    Compare(T a,T b):a(a),b(b){

    }
    T bigger()
    {
        if (a > b)
            return a;
        return b;
    }
};
int main(){
    int a,b;
    cin>>a>>b;
    Compare<int> c(a,b);
    cout<<c.bigger()<<endl;
}
