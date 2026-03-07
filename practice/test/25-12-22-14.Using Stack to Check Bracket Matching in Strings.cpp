/*【输入形式】
输入一个字符串，最大长度不超过100个字符，包含括号和其它字符，以空格分隔。例如："{ ()}[]"
【输出形式】
如果括号匹配且嵌套层次正确，输出"Balanced"；否则，输出"Not Balanced"。
【样例输入】
{()}[]
【样例输出】
Balanced
【样例说明】
输入的字符串中，括号成对出现且嵌套正确。
【实现提示】
  遇到左括号入栈，遇到右括号出栈， 出栈时检查是否匹配，最后栈为空则匹配。*/
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;
bool isBalanced(char expr[])
{
    stack<char> s;
    for (int i = 0; expr[i] != '\0'; i++)
    {
        char c = expr[i];
        if (c == '{' || c == '[' || c == '(')
        {
            s.push(c);
        }
        else if (c == '}' || c == ']' || c == ')')
        {
            if (s.empty())
                return false;
            char t = s.top();
            if (t == '{' && c == '}' ||
                t == '[' && c == ']' ||
                t == '(' && c == ')')
                s.pop();
            else
                return false;
        }
    }
    return s.empty();
}
// 在main函数中输入表达式，调用isBalanced函数，输出判断结果
int main()
{
    char expr1[100];
    cin >> expr1;
    cout << (isBalanced(expr1) ? "Balanced" : "Not Balanced") << endl; // 应输出判断结果
}
