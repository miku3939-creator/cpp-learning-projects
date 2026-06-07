#include <iostream>
#include <stack>
#include <string>
using namespace std;

// 二叉树结点结构
struct BTNode {
    char data;
    BTNode *lchild, *rchild;
    BTNode(char d) : data(d), lchild(nullptr), rchild(nullptr) {}
};

// 二叉树类
class BTree {
private:
    BTNode* root;  // 根结点

public:
    BTree() : root(nullptr) {}
    
    // 根据括号表示法创建二叉树
    void CreateBTree(string str) {
        stack<BTNode*> st;   // 辅助栈
        BTNode* p = nullptr;
        bool flag = true;    // true:处理左孩子, false:处理右孩子
        int i = 0;
        
        while (i < str.length()) {
            char ch = str[i];
            
            switch (ch) {
                case '(':   // 遇到 '('，表示前面创建的结点有孩子，将其入栈
                    st.push(p);
                    flag = true;   // 下一个结点是左孩子
                    break;
                    
                case ',':   // 遇到 ','，表示开始处理右孩子
                    flag = false;
                    break;
                    
                case ')':   // 遇到 ')'，表示当前结点的子树处理完毕，出栈
                    if (!st.empty())
                        st.pop();
                    break;
                    
                default:    // 遇到普通字符（结点值）
                    // 创建新结点
                    p = new BTNode(ch);
                    
                    // 如果是第一个结点，作为根结点
                    if (root == nullptr) {
                        root = p;
                    }
                    // 否则，根据 flag 决定作为左孩子还是右孩子
                    else {
                        if (!st.empty()) {
                            if (flag) {
                                st.top()->lchild = p;   // 作为左孩子
                            } else {
                                st.top()->rchild = p;   // 作为右孩子
                            }
                        }
                    }
                    break;
            }
            i++;
        }
    }
    
    // 输出括号表示法（用于验证）
    void DispBTree() {
        DispBTree(root);
        cout << endl;
    }
    
    void DispBTree(BTNode* b) {
        if (b != nullptr) {
            cout << b->data;
            if (b->lchild != nullptr || b->rchild != nullptr) {
                cout << "(";
                DispBTree(b->lchild);
                if (b->rchild != nullptr) {
                    cout << ",";
                    DispBTree(b->rchild);
                }
                cout << ")";
            }
        }
    }
    
    // 获取根结点（用于调试）
    BTNode* getRoot() { return root; }
};

int main() {
    string str = "A(B(D(,G)),C(E,F))";
    BTree bt;
    bt.CreateBTree(str);
    
    cout << "创建的二叉树括号表示法：";
    bt.DispBTree();
    
    return 0;
}