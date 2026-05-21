/*【问题描述】


给定一个s字符串和一个t字符串，在s字符串中找出t字符串出现的第一个位置（从0开始），如果不存在则返回-1。例如，输入s="hello"，t="ll"，输出结果为2。设计如下成员函数：




class Solution {
public:
 int strStr(string s, string t)
 {  …  }
};


【输入形式】

     输入两个字符串，先输入的为s串，后输入的为t串。字符串中允许出现空格符。


【输出形式】

     t串在s串中出现的第一个位置。若t串不在s串中，则返回-1。


【样例输入】

    hello

    ll


【样例输出】

    2


【样例说明】

      s串为“hello”，t串为“ll”，t串在s串中第一次出现的位置为2（从0开始计数）。测试数据存放在in.txt文件中。


【评分标准】

     共10个测试用例，每通过一个测试得10分。*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Solution {
public:
    int strStr(string s, string t) {
        if (t.empty()) return 0;
        int n = s.size();
        int m = t.size();
        if (n < m) return -1;

        vector<int> pi(m, 0);
        for (int i = 1; i < m; i++) {
            int j = pi[i - 1];
            while (j > 0 && t[i] != t[j])
                j = pi[j - 1];
            if (t[i] == t[j])
                j++;
            pi[i] = j;
        }
        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j > 0 && s[i] != t[j])
                j = pi[j - 1];
            if (s[i] == t[j])
                j++;
            if (j == m)
                return i - m + 1;
        }
        return -1;
    }
};

int main() {
    ifstream in("in.txt");
    if (!in.is_open()) return 0;

    string s, t;
    if (getline(in, s) && getline(in, t)) {
        Solution sol;
        cout << sol.strStr(s, t) << endl;
    }
    return 0;
}