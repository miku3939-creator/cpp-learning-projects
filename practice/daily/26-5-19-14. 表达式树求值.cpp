#include <iostream>
#include <vector>
#include <string>

using namespace std;

// 定义表达式树节点结构
struct TreeNode {
    int type;      // 0: 数字, 1: 运算符
    long long val; // 数字的值（用 long long 防止计算过程中溢出）
    char op;       // 运算符字符 (+, -, *, /)
    int left;      // 左子节点 ID
    int right;     // 右子节点 ID
};

// 预分配足够大的数组，直接用 ID 作为下标映射
TreeNode tree[100005];
bool has_parent[100005]; // 标记节点是否有父节点，用来找根节点
bool is_exist[100005];   // 标记这个 ID 的节点是否存在

// 递归后序遍历求值
long long evaluate(int root_id) {
    // 基础边界
    if (root_id == -1) return 0;
    
    // 如果是叶子节点（数字），直接返回它的值
    if (tree[root_id].type == 0) {
        return tree[root_id].val;
    }
    
    // 如果是内部节点（运算符），先递归计算左、右子树的值
    long long left_val = evaluate(tree[root_id].left);
    long long right_val = evaluate(tree[root_id].right);
    
    // 根据运算符进行计算（C++自带的 / 运算天然就是向零取整）
    switch (tree[root_id].op) {
        case '+': return left_val + right_val;
        case '-': return left_val - right_val;
        case '*': return left_val * right_val;
        case '/': return left_val / right_val; 
    }
    return 0;
}

int main() {
    // 提升输入输出效率
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int root_candidate = -1; // 用来记录可能作为起点的任意一个存在节点的ID

    for (int i = 0; i < n; i++) {
        int id, type, left, right;
        string val_str;
        
        cin >> id >> type >> val_str >> left >> right;
        
        tree[id].type = type;
        tree[id].left = left;
        tree[id].right = right;
        is_exist[id] = true;
        root_candidate = id; // 随便抓一个存在的节点开始

        if (type == 0) {
            // 数字：将字符串转换为数字
            tree[id].val = stoll(val_str);
        } else {
            // 运算符：提取第一个字符
            tree[id].op = val_str[0];
        }

        // 记录谁是谁的孩子，用来排除根节点
        if (left != -1) has_parent[left] = true;
        if (right != -1) has_parent[right] = true;
    }

    // 从任意一个存在的节点一路往上逆向找，或者全局扫一遍，找出唯一的根节点
    int root_id = -1;
    for (int i = 0; i < 100005; i++) {
        if (is_exist[i] && !has_parent[i]) {
            root_id = i;
            break;
        }
    }

    // 后序计算并输出结果
    cout << evaluate(root_id) << "\n";

    return 0;
}