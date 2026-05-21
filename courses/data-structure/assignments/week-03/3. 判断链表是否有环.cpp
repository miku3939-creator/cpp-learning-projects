#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int val;
    int next;
    Node(int val, int next) : val(val), next(next) {}
    Node() {}
};
int main()
{
    int n;
    cin >> n;
    int i = 0, j = i + 1;
    vector<Node> v;
    for (int i = 0; i < n; i++)
    {
        int val, next;
        cin >> val >> next;
        v.push_back(Node(val, next));
    }
    while (v[i].next != -1 && v[j].next != -1 && v[v[i].next - 1].next != -1)
    {
        if (i == j)
        {
            cout << "YES" << endl;
            return 0;
        }
        i = v[i].next - 1;
        j = v[v[j].next - 1].next - 1;
    }
    cout << "NO" << endl;
    return 0;
}
