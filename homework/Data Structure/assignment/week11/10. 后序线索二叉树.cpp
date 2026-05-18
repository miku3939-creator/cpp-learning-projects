#include <iostream>
#include <string>
using namespace std;

// 线索二叉树节点结构
struct ThreadedNode
{
    char data;
    ThreadedNode *lchild;
    ThreadedNode *rchild;
    ThreadedNode *parent; // 父指针，用于查找后序遍历的后继
    bool ltag;            // 0:左孩子 1:前驱线索
    bool rtag;            // 0:右孩子 1:后继线索

    ThreadedNode(char val) : data(val), lchild(nullptr), rchild(nullptr), parent(nullptr), ltag(0), rtag(0) {}
};

class PostOrderThreadedTree
{
private:
    ThreadedNode *root;
    ThreadedNode *pre; // 线索化时记录前驱节点
    int index;         // 构建树时的索引

    // 参见讲义7.5.2反序列化构建二叉树，注意需同时设置parent指针
    ThreadedNode *createTree(const string &preOrder, ThreadedNode *par)
    {
        if (index >= preOrder.size() || preOrder[index] == '#')
        {
            index++;
            return nullptr;
        }
        ThreadedNode *node = new ThreadedNode(preOrder[index]);
        index++;
        node->parent = par;

        node->lchild = createTree(preOrder, node);
        node->rchild = createTree(preOrder, node);

        return node;
    }

    // 递归后序线索化，类似讲义p217中序线索化
    // 线索化左子树
    // 线索化右子树
    // 建立当前节点的前驱线索
    // 建立前驱节点的后继线索
    // 更新前驱
    void postOrderThreading(ThreadedNode *node)
    {
        if (node == nullptr)
            return;

        postOrderThreading(node->lchild);
        postOrderThreading(node->rchild);

        if (node->lchild == nullptr)
        {
            node->ltag = 1;
            node->lchild = pre;
        }

        if (pre != nullptr && pre->rchild == nullptr)
        {
            pre->rtag = 1;
            pre->rchild = node;
        }

        pre = node;
    }

    // 返回后序遍历的第一个节点
    //  提示：一直向左下走，直到找到最左节点
    //  如果最左节点有右孩子，继续找右子树的第一个节点
    ThreadedNode *getFirstNode(ThreadedNode *node) const
    {
        if (node == nullptr)
            return nullptr;
        while (node->ltag == 0 || node->rtag == 0)
        {
            if (node->ltag == 0)
            {
                node = node->lchild;
            }
            else
            {
                node = node->rchild;
            }
        }
        return node;
    }

    // 返回节点在后序遍历中的后继（利用 parent 指针）
    // 如果右指针是线索，直接返回后继；
    // 如果有右子树，后继在祖先中寻找；
    // 如果是根节点，无后继
    // 如果 node 是 parent 的左孩子且 parent 有右孩子，后继为右子树的第一个节点
    ThreadedNode *getNextNode(ThreadedNode *node) const
    {
        if (node == nullptr)
            return nullptr;

        if (node->rtag == 1)
        {
            return node->rchild;
        }

        ThreadedNode *par = node->parent;
        if (par == nullptr)
            return nullptr;

        if (par->rchild == node || par->rtag == 1)
        {
            return par;
        }
        else
        {
            return getFirstNode(par->rchild);
        }
    }

    // 返回节点在后序遍历中的前驱
    // 如果左指针是线索，直接返回前驱
    // 如果左孩子存在，若右孩子也存在，前驱就是右孩子，否则前驱是左孩子
    ThreadedNode *getPrevNode(ThreadedNode *node) const
    {
        if (node == nullptr)
            return nullptr;

        if (node->ltag == 1)
        {
            return node->lchild;
        }

        if (node->rtag == 0)
        {
            return node->rchild;
        }
        else
        {
            return node->lchild;
        }
    }

    // 递归销毁二叉树
    void destroyTree(ThreadedNode *node)
    {
        if (node == nullptr)
            return;
        if (node->ltag == 0)
            destroyTree(node->lchild);
        if (node->rtag == 0)
            destroyTree(node->rchild);
        delete node;
    }

public:
    PostOrderThreadedTree() : root(nullptr), pre(nullptr), index(0) {}
    ~PostOrderThreadedTree() { destroyTree(root); }

    // 构建二叉树
    void buildTree(const string &preOrder)
    {
        index = 0;
        root = createTree(preOrder, nullptr);
    }

    // 后序线索化主程序
    void threadTree()
    {
        pre = nullptr;
        if (root != nullptr)
        {
            postOrderThreading(root);
            // 处理最后一个节点的右线索
            if (pre->rchild == nullptr)
            {
                pre->rtag = 1;
                pre->rchild = nullptr; // 最后一个节点后继为空
            }
        }
    }

    // 非递归后序遍历
    void postOrderTraversal() const
    {
        ThreadedNode *p = getFirstNode(root);
        bool first = true;
        while (p != nullptr)
        {
            if (!first)
                cout << " ";
            cout << p->data;
            first = false;
            p = getNextNode(p);
        }
        cout << endl;
    }

    // 按值查找节点（利用后序遍历）
    ThreadedNode *findNode(char val) const
    {
        ThreadedNode *p = getFirstNode(root);
        while (p != nullptr)
        {
            if (p->data == val)
                return p;
            p = getNextNode(p);
        }
        return nullptr;
    }

    // 返回指定值的前驱（若节点不存在则返回 nullptr）
    ThreadedNode *getPrev(char val)
    {
        ThreadedNode *node = findNode(val);
        return getPrevNode(node);
    }

    // 返回指定值的后继（若节点不存在则返回 nullptr）
    ThreadedNode *getNext(char val)
    {
        ThreadedNode *node = findNode(val);
        return getNextNode(node);
    }
};

// 主函数
int main()
{
    string preOrder;
    char target;

    // 正确读取两行输入
    getline(cin, preOrder);
    cin >> target;

    PostOrderThreadedTree tree;
    tree.buildTree(preOrder);
    tree.threadTree();

    // 输出后序遍历序列
    tree.postOrderTraversal();

    // 查找目标节点并输出前驱和后继（改用公有接口）
    ThreadedNode *prev = tree.getPrev(target);
    ThreadedNode *next = tree.getNext(target);

    prev ? cout << prev->data : cout << "NULL";
    cout << " ";
    next ? cout << next->data : cout << "NULL";
    cout << endl;

    return 0;
}
