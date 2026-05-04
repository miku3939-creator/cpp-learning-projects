#include <iostream>
#include <stack>
#include <string>
#include <fstream>
using namespace std;
class expcomp
{
public:
    string s;
    string res;
    int val;

    expcomp(string s) : s(s), res("") {}
    void change()
    {
        stack<char> s;
        int i = 0;
        while (i < s1.size())
        {
            char ch = s1[i];
            if (ch == '(')
            {
                s.push(ch);
            }
            else if (ch == ')')
            {
                while (!s.empty() && s.top() != '(')
                {
                    res1 += s.top();
                    s.pop();
                }
                s.pop();
            }
            else if (ch == '+' || ch == '-')
            {
                while (!s.empty() && s.top() != '(')
                {
                    res1 += s.top();
                    s.pop();
                }
                s.push(ch);
            }
            else if (ch == '/' || ch == '*')
            {
                while (!s.empty() && s.top() != '(' && (s.top() == '*' || (s.top() == '/')))
                {
                    res1 += s.top();
                    s.pop();
                }
                s.push(ch);
            }
            else
            {
                string d = "";
                if ((ch >= 'a' && ch <= 'z'))
                {
                    d = ch;
                    res1 += d;
                    res1 += "#";
                }
                while ((ch >= '0' && ch <= '9'))
                {
                    d += ch;
                    i++;
                    if (i < s1.size())
                    {
                        ch = s1[i];
                    }
                    else
                        break;
                }
                i--;
                res1 += d;
                res1 += "#";
            }
            i++;
        }
        while (!s.empty())
        {
            res1 += s.top();
            s.pop();
        }
    }
    bool getval(ostream &out, int k)
    {
        stack<int> fig;
        int a, b;
        char ch;
        int i = 0;
        while (i < res1.size())
        {
            string c = "";
            ch = res1[i];
            switch (ch)
            {

            case '+':
                b = fig.top();
                fig.pop();
                a = fig.top();
                fig.pop();
                fig.push(a + b);
                break;
            case '-':
                b = fig.top();
                fig.pop();
                a = fig.top();
                fig.pop();
                fig.push(a - b);
                break;
            case '*':
                b = fig.top();
                fig.pop();
                a = fig.top();
                fig.pop();
                fig.push(a * b);
                break;
            case '/':
                b = fig.top();
                fig.pop();
                a = fig.top();
                fig.pop();
                if (b == 0)
                {
                    out << "表达式" << k << "除0出错!" << endl;
                    return false;
                }
                fig.push(a / b);
                break;

            default:

                if (ch >= 'a' && ch <= 'z')
                {
                    fig.push(ch);
                    break;
                }
                while (ch >= '0' && ch <= '9')
                {
                    c += ch;
                    i++;
                    ch = res1[i];
                }
                fig.push(stoi(c));
                break;
            }
            i++;
        }
        val1 = fig.top();
        fig.pop();
        return true;
    }

    bool isOp(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
    bool isvaild(ostream &out, int k)
    {
        stack<char> st;
        int len = s1.size();
        if (len == 0)
        {
            out << "表达式" << k << "无效!" << endl;
            return false;
        }
        for (int i = 0; i < len; i++)
        {
            char c = s1[i];
            if (!isalnum(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')')
            {
                out << "表达式" << k << "无效!" << endl;
            }
            if (c == '(')
                st.push(c);
            else if (c == ')')
            {
                if (st.empty())
                {
                    out << "表达式" << k << "无效!" << endl;
                    return false;
                }
                st.pop();
            }
            if (i < len - 1)
            {
                char next = s1[i + 1];
                // 运算符后面不能接运算符或右括号
                if (isOp(c) && (isOp(next) || next == ')'))
                {
                    out << "表达式" << k << "无效!" << endl;
                    return false;
                }
                // 左括号后面不能接运算符或右括号
                if (c == '(' && (next == '+' || next == '-' || next == '*' || next == '/' || next == ')'))
                {
                    out << "表达式" << k << "无效!" << endl;
                    return false;
                }
                // 操作数后面不能直接跟操作数或左括号 (a b 或 3(a))
                if (isalnum(c) && (isalnum(next) || next == '('))
                {
                    out << "表达式" << k << "无效!" << endl;
                    return false;
                }
            }
        }
        // 首尾检查
        if (isOp(s1[0]) || isOp(s1[len - 1]) || s1[0] == ')' || s1[len - 1] == '(')
        {
            out << "表达式" << k << "无效!" << endl;
            return false;
        }

        if (!st.empty())
        {
            out << "表达式" << k << "无效!" << endl;
            return false;
        } // 检查括号是否都闭合

        return true;
    }
  
};
  void comp(ostream &out,expcomp &s1,expcomp &s2)
    {
        if (!isvaild(out))
            return;
        change();
        if (!getval(out))
            return;
        if (val1 == val2)
            out << "TRUE" << endl;
        else
            out << "FALSE" << endl;
    }
int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");

    int n;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        out << "测试用例" << i + 1 << ": ";
        string s1, s2;
        in >> s1 >> s2;
        expcomp e(s1, s2);
        e.comp(out);
    }
    return 0;
}