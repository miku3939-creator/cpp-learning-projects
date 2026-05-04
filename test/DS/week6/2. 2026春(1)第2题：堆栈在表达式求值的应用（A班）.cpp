/* 返回

2. 2026春(1)第2题：堆栈在表达式求值的应用（A班）
【问题描述】

数学老师需快速验证学生书写的算术表达式与标准答案是否等效，现要求编写C++程序，通过计算表达式结果的方式实现判断逻辑。

【实验要求】

（1）输入规则：第一行输入正整数n（表示需判断的算术表达式对数/测试用例数，1≤n≤20）；

后续输入n对算术表达式，每对表达式各占一行（无空行），单个表达式长度不超过20个字符。

（2）表达式构成：包含运算符（ + 、-、*、/）、运算数（一位数字或单个大小写区别的字母） 、输入表达式可能有语法错误，需要有效性验证。

（3）计算规则：除号“/”按整数除法规则计算（结果取整，例如5/3结果为1，分母为0表示表达式除0出错）；必须通过逆波兰式（后缀表达式）完成表达式的计算逻辑。

【输入格式】in.txt文件输入n个测试用例

（1）第一行：正整数n（测试用例数量，1≤n≤20）。

（2）后续2n行：每2行对应1个测试用例，即每个测试用例包含两个算术表达式（各占一行）。

【输出格式】文件out.txt输出共n行，对应n个对表达式的判断结果：若第i对表达式计算结果等效，第i行输出：TRUE”；否则输出“FALSE”。若第i对表达式的第j个表达式是无效表达式，第i行输出：表达式j无效！若第i对表达式的第j个表达式除0错误，第i行输出：表达式j除0出错。

【样例输入】输入文件in.txt内容如下：                        

4

3*(a+2*3/(2+1))-b*(5-2)

(b+1)*(5-3)+3-(6-4)*c

6+5+4+3+2

4*(2+6/3)+2

(a+b)*(-b)

a*a-b*b

5-4+8/(7-6/2-9/2)

2*3-8

【样例输出】输出文件out.txt如下:

测试用例1：TRUE

测试用例2：FALSE

测试用例3：表达式1无效！

测试用例4：表达式1除0出错！

【评分标准】

5组测试用例，每通过一个测试用例得20分*/
#include <iostream>
#include <stack>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

class expvalue
{
public:
    string src;
    string res;
    int val;

    expvalue(string s) : src(s) {}

    bool isOp(char c)
    {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    int precedence(char op)
    {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        return 0;
    }

    bool isvaild()
    {
        stack<char> st;
        int len = src.size();
        if (len == 0) return false;

        for (int i = 0; i < len; i++)
        {
            char c = src[i];
            if (!isalnum(c) && !isOp(c) && c != '(' && c != ')')
                return false;
            if (c == '(')
                st.push(c);
            else if (c == ')')
            {
                if (st.empty()) return false;
                st.pop();
            }
            if (i < len - 1)
            {
                char next = src[i + 1];
                if (isOp(c) && (isOp(next) || next == ')')) return false;
                if (c == '(' && (isOp(next) || next == ')')) return false;
                if (isalnum(c) && (isalnum(next) || next == '(')) return false;
            }
        }
        if (isOp(src[0]) || isOp(src[len - 1]) || src[0] == ')' || src[len - 1] == '(')
            return false;
        if (!st.empty()) return false;
        return true;
    }

    void trans()
    {
        res.clear();  // 清空之前的结果
        stack<char> s;
        int i = 0;
        int len = src.size();

        while (i < len)
        {
            char ch = src[i];
            if (ch == '(')
            {
                s.push(ch);
                i++;
            }
            else if (ch == ')')
            {
                while (!s.empty() && s.top() != '(')
                {
                    res += s.top();
                    s.pop();
                }
                if (!s.empty()) s.pop();
                i++;
            }
            else if (isOp(ch))
            {
                while (!s.empty() && s.top() != '(' && precedence(s.top()) >= precedence(ch))
                {
                    res += s.top();
                    s.pop();
                }
                s.push(ch);
                i++;
            }
            else if (isalpha(ch))
            {
                res += ch;
                res += '#';
                i++;
            }
            else if (isdigit(ch))
            {
                string num;
                while (i < len && isdigit(src[i]))
                {
                    num += src[i];
                    i++;
                }
                res += num;
                res += '#';
                // 此时 i 已指向数字后的字符，不用再 ++
            }
            else
            {
                i++;
            }
        }
        while (!s.empty())
        {
            res += s.top();
            s.pop();
        }
    }

    bool getval()
    {
        stack<int> fig;
        int i = 0;
        int len = res.size();

        while (i < len)
        {
            char ch = res[i];
            if (isOp(ch))
            {
                if (fig.size() < 2) return false;
                int b = fig.top(); fig.pop();
                int a = fig.top(); fig.pop();
                switch (ch)
                {
                case '+': fig.push(a + b); break;
                case '-': fig.push(a - b); break;
                case '*': fig.push(a * b); break;
                case '/':
                    if (b == 0) return false;
                    fig.push(a / b);
                    break;
                }
                i++;
            }
            else if (isdigit(ch))
            {
                int num = 0;
                while (i < len && isdigit(res[i]))
                {
                    num = num * 10 + (res[i] - '0');
                    i++;
                }
                fig.push(num);
            }
            else if (isalpha(ch))
            {
                fig.push((int)ch);
                i++;
            }
            else if (ch == '#')
            {
                i++;
            }
            else
            {
                i++;
            }
        }

        if (fig.empty()) return false;
        val = fig.top();
        return true;
    }
};

int main()
{
    ifstream in("in.txt");
    ofstream out("out.txt");

    if (!in.is_open() || !out.is_open())
    {
        cerr << "文件打开失败" << endl;
        return 1;
    }

    int n;
    in >> n;
    in.ignore();

    for (int i = 0; i < n; i++)
    {
        string s1, s2;
        getline(in, s1);
        getline(in, s2);

        expvalue e1(s1), e2(s2);
        bool valid1 = e1.isvaild();
        bool valid2 = e2.isvaild();

        out << "测试用例" << i + 1 << "：";

        if (!valid1 && !valid2)
        {
            out << "表达式1无效！表达式2无效！" << endl;
            continue;
        }
        if (!valid1)
        {
            out << "表达式1无效！" << endl;
            continue;
        }
        if (!valid2)
        {
            out << "表达式2无效！" << endl;
            continue;
        }

        e1.trans();
        e2.trans();

        bool ok1 = e1.getval();
        bool ok2 = e2.getval();

        if (!ok1 && !ok2)
        {
            out << "表达式1除0出错！表达式2除0出错！" << endl;
            continue;
        }
        if (!ok1)
        {
            out << "表达式1除0出错！" << endl;
            continue;
        }
        if (!ok2)
        {
            out << "表达式2除0出错！" << endl;
            continue;
        }

        if (e1.val == e2.val)
            out << "TRUE" << endl;
        else
            out << "FALSE" << endl;
    }

    in.close();
    out.close();
    return 0;
}