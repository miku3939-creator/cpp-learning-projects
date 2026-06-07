#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;
struct Solution
{
    vector<vector<int>> G;
    vector<int> ans; // 存放i的入边邻接点
    int n, m, i;     // 注意不要使用i作为循环变量了
    Solution()
    {
        cin >> n >> m;
        G.resize(n + 1); // 点的编号为1~n
        while (m--)
        {
            int u, v;
            cin >> u >> v;
            G[u].push_back(v);
        }
        cin >> i;
    }
    void solve()
    {
        for (int j = 1; j < n + 1; j++)
        {
            for (int k : G[j])
            {
                if (k == i)
                    ans.push_back(j);
            }
        }
    }
};

int main()
{
    Solution s;
    s.solve();
    sort(s.ans.begin(), s.ans.end());
    for (auto r : s.ans)
        cout << r << " ";
    cout << "\n";
}
