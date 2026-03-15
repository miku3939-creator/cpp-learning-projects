

/*
题7_回文字符串判断【题目描述】
给定一个字符串 s，判断它是否为回文串。
如果从左往右读和从右往左读完全相同，则为回文串。

【输入格式】
共 6 行，每行一个不含空格的字符串。

【输出格式】
对于每组测试：
若是回文串，输出 Yes
否则输出 No

【说明】
区分大小写。*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    for (int i = 0; i < n / 2; i++)
    {
        if (s[i] != s[n - i - 1])
            cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    return 0;
}
