/*
 * @lc app=leetcode.cn id=150 lang=cpp
 *
 * [150] 逆波兰表达式求值
 */

// @lc code=start
class Solution
{
public:
    bool isN(string &token)
    {
        return !(token == "+" ||token == "-" || token == "*" || token == "/");
    }

    int evalRPN(vector<string> &tokens)
    {
        stack<int> s;
        int n = tokens.size();
        for (int i = 0; i<n; i++)
        {
            string &token = tokens[i];
            if (isN(token))
            {
                s.push(stoi(token));
            }
            else
            {
                int a = s.top();
                s.pop();
                int b = s.top();
                s.pop();
                switch (token[0])
                {
                case '+':
                    s.push(a + b);
                    break;
                case '-':
                    s.push(b - a);
                    break;
                case '*':
                    s.push(a * b);
                    break;
                case '/':
                    s.push(b / a);
                }
            }
        }
        return s.top();
    }
};
// @lc code=end
