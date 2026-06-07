/*【实验题目】从标准输入读取一个合法算术运算表达式（示例：(a + 3)*2/(b-A)），完成以下任务：

（1）根据输入表达式构建表达式二叉树。

（2）基于表达式树计算原表达式的值。

（3）对表达式树进行层次遍历，并输出遍历结果的倒序。

（4）按照层次遍历的倒序结果，重新计算表达式的值。

如表达式为(a + 3)*2/(b-A)，则生成的表达式树为如下图，通过表达式树计算的值为6，层次遍历倒序为：3aAb2 + -*//*，根据层次遍历倒序结果计算表达式的值为6。

【实验要求】

（1）输入限制：单个算术表达式长度不超过20个字符，表达式语法合法，圆括号正确匹配且支持嵌套，无错误表达式。 

（2）表达式组成：①运算符：+（加）、-（减）、*（乘）、/（除）；②运算数：一位十进制

数字、单个英文字母（A-Z/a-z），字母以其ASCII码值参与数值运算；③边界符：正确匹配的左圆括号"（"和右圆括号"）"。

（3）运算规则：除法运算采用整数除法，结果取整数部分（例：5/3=1）。



blob.png



【输入格式】从键盘输入一个合法的算术表达式字符串。

输入示例：(a+3)*2/(b-A)

【输出格式】在屏幕上依次输出以下三行内容：

第一行：基于表达式树计算得出的原表达式数值。

第二行：表达式树层次遍历结果的倒序序列。

第三行：依据层次遍历倒序结果计算得到的数值。

对于上述输入，输出一次为：

6

3aAb2 + -*/

/*6*/
#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char c) : val(c), left(nullptr), right(nullptr) {}
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// 中缀转后缀
string infixToPostfix(const string& exp) {
    stack<char> st;
    string post;

    for (char ch : exp) {
        if (isalnum(ch)) {
            post += ch;
        }
        else if (ch == '(') {
            st.push(ch);
        }
        else if (ch == ')') {
            while (!st.empty() && st.top() != '(') {
                post += st.top();
                st.pop();
            }
            st.pop();
        }
        else {
            while (!st.empty() &&
                   priority(st.top()) >= priority(ch)) {
                post += st.top();
                st.pop();
            }
            st.push(ch);
        }
    }

    while (!st.empty()) {
        post += st.top();
        st.pop();
    }

    return post;
}

// 后缀表达式建树
TreeNode* buildTree(const string& post) {
    stack<TreeNode*> st;

    for (char ch : post) {
        if (isalnum(ch)) {
            st.push(new TreeNode(ch));
        }
        else {
            TreeNode* node = new TreeNode(ch);

            node->right = st.top();
            st.pop();

            node->left = st.top();
            st.pop();

            st.push(node);
        }
    }

    return st.top();
}

// 计算表达式树
int evaluate(TreeNode* root) {
    if (!root) return 0;

    if (isalnum(root->val)) {
        if (isdigit(root->val))
            return root->val - '0';
        else
            return (int)root->val;
    }

    int l = evaluate(root->left);
    int r = evaluate(root->right);

    switch (root->val) {
        case '+': return l + r;
        case '-': return l - r;
        case '*': return l * r;
        case '/': return l / r;
    }

    return 0;
}

// 层次遍历逆序
string reverseLevelOrder(TreeNode* root) {
    queue<TreeNode*> q;
    string level;

    q.push(root);

    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();

        level += cur->val;

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }

    reverse(level.begin(), level.end());

    return level;
}

// 根据逆序层次遍历恢复表达式树
TreeNode* rebuildTree(const string& rev) {
    string level = rev;
    reverse(level.begin(), level.end());

    TreeNode* root = new TreeNode(level[0]);

    queue<TreeNode*> q;
    q.push(root);

    int idx = 1;

    while (!q.empty() && idx < level.size()) {
        TreeNode* cur = q.front();
        q.pop();

        if (isOperator(cur->val)) {
            cur->left = new TreeNode(level[idx++]);
            q.push(cur->left);

            if (idx < level.size()) {
                cur->right = new TreeNode(level[idx++]);
                q.push(cur->right);
            }
        }
    }

    return root;
}

int main() {
    string expr;
    cin >> expr;

    string postfix = infixToPostfix(expr);

    TreeNode* root = buildTree(postfix);

    cout << evaluate(root) << endl;

    string rev = reverseLevelOrder(root);
    cout << rev << endl;

    TreeNode* root2 = rebuildTree(rev);

    cout << evaluate(root2) << endl;

    return 0;
}