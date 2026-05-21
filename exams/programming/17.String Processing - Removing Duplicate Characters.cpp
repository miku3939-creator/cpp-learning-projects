/*字符串处理-删除重复字符
【问题描述】
编程实现DeleteSame函数的功能。假设有如下的函数调用：num=DeleteSame(oldstr, newstr)；其中，oldstr是字符串，该函数删除字符串oldstr中重复出现的字符，只保留首次出现的各个字符，将结果保存至字符串newstr，并且返回被删除的字符个数。
说明：
1.函数原型：int DeleteSame(char *oldstr, char *newstr)；
2.字符串最长为49个字符。
【输入形式】
输入字符串oldstr，该字符串中重复出现的字符将被删除，只保留首次出现的各个字符
【输出形式】
输出字符串newstr（只保留字符串oldstr中首次出现的各个字符），被删除的字符个数。
【样例输入】
样例输入1
The-value=of=pi=is-3.1415926535
样例输入2
helloC++
【样例输出】
样例输出1
The-valu=ofpis3.145926 9
样例输出2
heloC+ 2
【样例说明】
暂无
【评分标准】
每个测试用例2分，共10分*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string o;
    cin >> o;
    string n;
    for (auto &e : o)
    {
        if (n.find(e) ==string::npos)
        {
            n += e;
        }
    }
    for (auto &e : n)
    {
        cout << e;
    }
    cout << ' ';
    cout << o.size() - n.size();
    return 0;
}
