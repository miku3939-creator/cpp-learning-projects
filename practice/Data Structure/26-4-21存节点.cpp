#include <iostream>
#include <vector>
using namespace std;

struct node
{
    char data;
    int parent;
    node(char d, int p)
    {
        data = d;
        parent = p;
    }
};

int level(vector<node> &t, int i)
{
    if (i == -1 || i > t.size())
        return 0;
    int x = 1;
    while (t[i].parent != -1)
    {
        i = t[i].parent;
        x++;
    }
    return x;
}
int main()
{
    vector<node> t;
    t.push_back(node('A', -1));
    t.push_back(node('B', 0));
    t.push_back(node('C', 0));
    t.push_back(node('D', 1));
    t.push_back(node('E', 1));
    t.push_back(node('F', 1));
    t.push_back(node('G', 4));
    for (int i = 0; i < t.size(); i++)
        cout << t[i].data << ' ' << level(t, i) << endl;
    return 0;
}
