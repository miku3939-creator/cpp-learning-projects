#include <iostream>
#include <stack>
using namespace std;
class Express // 求表达式值类
{
    string source;
    string result;

public:
    Express(string str)
    {
        source = str;
        result = "";
    }
    string getresult()
    {
        return result;
    }
    void Trans()
    {
        stack<char> oper;
        int i = 0;
        char ch;
        while (i < source.size())
        {
            ch = source[i];
            if (ch == '(')
                oper.push(ch);
            else if (ch == ')')
            {
                while (!oper.empty() && oper.top() != '(')
                {
                    result += oper.top();
                    oper.pop();
                }
                oper.pop();
            }
            else if (ch == '+' || ch == '-')
            {
                while (!oper.empty() && oper.top() != '(')
                {
                    result += oper.top();
                    oper.pop();
                }
                oper.push(ch);
            }
            else if (ch == '*' || ch == '/')
            {
                while (!oper.empty() && oper.top() != '(' && (oper.top() == '*' || oper.top() == '/'))
                {
                    result += oper.top();
                    oper.pop();
                }
                oper.push(ch);
            }
            else
            {
                string d = "";
                while (ch >= '0' && ch <= '9')
                {
                    d += ch;
                    i++;
                    if (i < source.size())
                        ch = source[i];
                    else
                        break;
                }
                i--;
                result += d;
                result += "#";
            }
            i++;
        }
        while (!oper.empty())
        {
            result += oper.top();
            oper.pop();
        }
    }
    double getvalue()
    {
        stack<double> opand;
        double a, b, c = 0;
        char ch;
        int i = 0;
        while (i < result.size())
        {
            ch = result[i];
            switch (ch)
            {
            case '+':
                b = opand.top();
                opand.pop();
                a = opand.top();
                opand.pop();
                opand.push(a + b);
                break;
            case '-':
                b = opand.top();
                opand.pop();
                a = opand.top();
                opand.pop();
                opand.push(a - b);
                break;
            case '*':
                b = opand.top();
                opand.pop();
                a = opand.top();
                opand.pop();
                opand.push(a * b);
                break;
            case '/':
                b = opand.top();
                opand.pop();
                a = opand.top();
                opand.pop();
                opand.push(a / b);
                break;
            default:
                while (ch >= '0' && ch <= '9')
                {
                    c = 10 * c + ch - '0';
                    i++;
                    ch = result[i];
                }
                opand.push(c);
                c = 0;
                break;
            }
            i++;
        }
        return opand.top();
    }
};
int main()
{
    string str;
    cin >> str;
    Express obj(str);
    cout << "source: " << str << endl;
    cout << "turn to result: " << endl;
    obj.Trans();
    cout << "result: " << obj.getresult() << endl;
    cout << "get value: " << endl;
    cout << "value: " << obj.getvalue() << endl;
    return 0;
}