/*【问题描述】
编写一函数expand(s1,s2)，用以将字符串s1中的缩记符号在字符串s2中扩展为等价的完整字符，
例如将a-d扩展为abcd。该函数可以处理大小写字母和数字，并可以处理a-b-c、a-z0-9与-a-z等类似的情况。
在main函数中测试该函数：从键盘输入包含缩记符号的字符串，然后调用该函数进行扩展，输出扩展结果。
注意：
待扩展字符串中有可能包含空格，例如：a-d x-z应扩展成：abcd xyz。
所以读入待扩展字符串时，应能够读入包含空格的字符串。
只要缩记符号-之后的字符比之前的字符的ASCII码值大，就要将它们之间的所有字符扩展出来
，例如：Z-a之间的字符也要扩展出来；
特殊情况：a-b-c将被扩展为：abc。a-a将被扩展为：a-a。
【输入形式】
从键盘输入包含扩展符的字符串
【输出形式】
输出扩展后的字符串
【输入样例】
a-c-u-B
【输出样例】
abcdefghijklmnopqrstu-B
abcdefghijklmnopqrstu-B
【样例说明】
扩展输入a-c-u为：abcdefghijklmnopqrstu，而B比u值小，所以无法扩展，直接输出。*/

/*#include <iostream>
#include <string>
using namespace std;

void expand(const string& s1, string& s2) {
    s2.clear();

    for (size_t i = 0; i < s1.length(); i++) {
        // 如果不是'-'，或者是第一个/最后一个字符，或者是无法扩展的'-'
        if (s1[i] != '-' || i == 0 || i == s1.length() - 1) {
            s2.push_back(s1[i]);
        } else {
            // 当前是'-'，且不在开头或结尾
            char prev = s1[i-1];
            char next = s1[i+1];

            // 检查是否可以扩展
            if (prev < next) {
                // 扩展prev+1到next
                // 但prev可能已经输出过了（比如a-b-c的情况）
                // 我们需要检查s2的最后一个字符

                // 从prev+1开始，避免重复输出prev
                for (char c = prev + 1; c <= next; c++) {
                    s2.push_back(c);
                }
                i++;  // 跳过next字符
            } else {
                // 不能扩展，输出'-'
                s2.push_back('-');
            }
        }
    }
}

int main() {
    string input, output;
    getline(cin, input);
    expand(input, output);
    cout << output << endl;
    return 0;
}*/

#include <string>
#include <iostream>
using namespace std;
void expand(string &s, string &s2)
{
    char p;
    char n;
    int l= s.size();
    for (int i = 0; i <l; i++)
    {
        if (s[i] != '-' || i == 0 || i == l- 1)
        {
            s2 += s[i];
        }
        else
        {
            p = s[i - 1];
            n = s[i + 1];
            if (p < n)
            {
                for (char j = p + 1; j < n; j++)
                {
                    s2 += j;
                }
            }
            else
            {
                s2 += s[i];
            }
        }
    }
}
int main()
{
    string s1, s2;
    getline(cin, s1);
    expand(s1, s2);
    cout << s2 << endl;
    return 0;
}
