#include <iostream>
#include <string>
using namespace std;

// 手动实现 BST 节点
struct Node {
    int val;
    Node* lc;
    Node* rc;
    Node(int v) : val(v), lc(nullptr), rc(nullptr) {}
};

// 1. INSERT 操作：插入元素 x
Node* insertBST(Node* root, int x) {
    if (root == nullptr) {
        return new Node(x);
    }
    if (x < root->val) {
        root->lc = insertBST(root->lc, x);
    } else if (x > root->val) {
        root->rc = insertBST(root->rc, x);
    }
    // 若已存在 (x == root->val)，根据题目要求忽略，直接返回
    return root;
}

// 2. FIND 操作：查找元素 x
bool findBST(Node* root, int x) {
    Node* curr = root;
    while (curr != nullptr) {
        if (x == curr->val) return true;
        else if (x < curr->val) curr = curr->lc;
        else curr = curr->rc;
    }
    return false;
}

// 辅助函数：找到以 root 为根的树的最小值节点（用于删除操作）
Node* getMinNode(Node* root) {
    while (root && root->lc != nullptr) {
        root = root->lc;
    }
    return root;
}

// 3. DELETE 操作：删除元素 x，用 bool 引用标记是否成功找到并删除
Node* deleteBST(Node* root, int x, bool& found) {
    if (root == nullptr) {
        found = false;
        return nullptr;
    }

    if (x < root->val) {
        root->lc = deleteBST(root->lc, x, found);
    } else if (x > root->val) {
        root->rc = deleteBST(root->rc, x, found);
    } else {
        // 找到了要删除的节点！
        found = true;
        
        // 情况 1 & 2：左孩子为空或右孩子为空
        if (root->lc == nullptr) {
            Node* temp = root->rc;
            delete root;
            return temp;
        } else if (root->rc == nullptr) {
            Node* temp = root->lc;
            delete root;
            return temp;
        }

        // 情况 3：左右孩子都存在
        // 找到右子树的最小值（后继节点）
        Node* successor = getMinNode(root->rc);
        // 用后继节点的值覆盖当前节点的值
        root->val = successor->val;
        // 递归去右子树中删除那个作为“替罪羊”的后继节点
        bool dummy = false;
        root->rc = deleteBST(root->rc, successor->val, dummy);
    }
    return root;
}

int main() {
    // 强制解除流同步，防止 10 万级操作导致 TLE 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    if (!(cin >> m)) return 0;

    Node* root = nullptr;
    string op;
    int x;

    while (m--) {
        cin >> op;
        if (op == "INSERT") {
            cin >> x;
            root = insertBST(root, x);
        } 
        else if (op == "DELETE") {
            cin >> x;
            bool found = false;
            root = deleteBST(root, x, found);
            if (!found) {
                cout << "NOT FOUND\n";
            }
        } 
        else if (op == "FIND") {
            cin >> x;
            if (findBST(root, x)) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        } 
        else if (op == "MIN") {
            if (root == nullptr) {
                cout << "EMPTY\n";
            } else {
                Node* minNode = getMinNode(root);
                cout << minNode->val << "\n";
            }
        } 
        else if (op == "MAX") {
            if (root == nullptr) {
                cout << "EMPTY\n";
            } else {
                // 一路向右死磕到底就是最大值
                Node* curr = root;
                while (curr->rc != nullptr) {
                    curr = curr->rc;
                }
                cout << curr->val << "\n";
            }
        }
    }

    return 0;
}