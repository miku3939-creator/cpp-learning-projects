/*13. 并查集-路径压缩与按秩合并
并查集-路径压缩与按秩合并
一、问题描述
实现一个并查集（Union-Find），支持以下操作：

union x y：合并包含x和y的集合

query x：查找x所在集合的代表元素（根节点）以及集合大小

same x y：判断x和y是否在同一个集合

要求实现路径压缩和按秩合并优化。

二、输入形式
第一行输入两个正整数n和m（1 ≤ n ≤ 100000, 1 ≤ m ≤ 100000），分别表示元素数量和操作数量。
接下来m行，每行一个操作，格式如上所述。元素编号为0到n-1。

三、输出形式
对于 query 操作，输出代表元素和集合大小，空格分隔。

对于 same 操作，输出 "Yes" 或 "No"。
每个输出占一行。

四、样例输入

5 6
union 0 1
union 2 3
query 0
same 0 2
union 1 2
same 0 3
五、样例输出
0 2
No
Yes
六、样例说明
操作过程：

union 0 1：集合{0,1}, {2}, {3}, {4}

union 2 3：集合{0,1}, {2,3}, {4}

query 0：代表元素为0（或1），集合大小为2，输出 0 2

same 0 2：不在同一集合，输出 No

union 1 2：合并{0,1}和{2,3}，得到{0,1,2,3}

same 0 3：在同一集合，输出 Yes

七、评分标准
共10个测试用例。

八、类库使用要求
只能使用数组实现并查集，禁止使用其他数据结构。*/ \
#include<iostream>
#include <vector>
using namespace std;
vector<int> v;
vector<int> s;
int find(int x)
{
    if (v[x] == x)
        return x;
    else
        return v[x] = find(v[x]);
}

void Union(int x, int y)
{
    int rootx = find(x);
    int rooty = find(y);
    if (rootx != rooty)
    {
        if (s[rootx] < s[rooty])
        {
            v[rootx] = rooty;
            s[rooty] += s[rootx];
        }
        else
        {
            v[rooty] = rootx;
            s[rootx] += s[rooty];
        }
    }
}
int main()
{
    int n, m, a, b;
    cin >> n >> m;
    v.resize(n);
    s.resize(n, 1);
    for (int i = 0; i < n; i++)
    {
        v[i] = i;
    }
    string op;
    for (int i = 0; i < m; i++)
    {
        cin >> op;
        if (op == "union")
        {
            cin >> a >> b;
            Union(a, b);
        }
        else if (op == "same")
        {
            cin >> a >> b;
            if (find(a) == find(b))
                cout << "Yes" << endl;
            else
                cout << "No" << endl;
        }
        else if (op == "query")
        {
            cin >> a;
            int r=find(a);
            cout <<r<<' '<<s[r] <<endl;
        }
    }
    return 0;
}