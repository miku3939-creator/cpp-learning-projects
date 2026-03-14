/*
 * @lc app=leetcode.cn id=20 lang=cpp
 *
 * [20] 有效的括号
 */

// @lc code=start
class Solution
{
public:
    bool isValid(string s)
    {
        stack<char> t;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                t.push(s[i]);
            else
            {
                if (t.empty())
                    return false;
                if ((s[i] == ')' && t.top() == '(') ||
                    (s[i] == '}' && t.top() == '{') ||
                    (s[i] == ']' && t.top() == '['))
                    t.pop();
                else
                    return false;
            }
        }
        return t.empty();
    }
};
// @lc code=end
