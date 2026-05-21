#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int partition(vector<int> &v, int fir, int las)
{
    int pivot = v[las];
    int i = fir - 1;

    for (int j = fir; j < las; j++)
    {
        if (v[j] < pivot)
        {
            i++;
            swap(v[i], v[j]);
        }
    }
    swap(v[i + 1], v[las]);
    return i + 1;
}
void quicksort(vector<int> &v, int fir, int las)
{
    if (fir < las)
    {
        int index = partition(v, fir, las);
        quicksort(v, fir, index - 1);
        quicksort(v, index + 1, las);
    }
}
int reduce(vector<int> &v)
{
    int i = 0;
    int j = 0;
    int n = v.size();
    while (j <= n - 1)
    {
        if (v[j] == v[i])
        {
            j++;
        }
        else
        {
            i++;
            swap(v[i], v[j]);
            j++;
        }
    }
    return i + 1;
}
int main()
{
    ifstream in("in.txt");
    if (!in.is_open())
    {
        cout << " 文件打开失败" << endl;
        return 1;
    }
    int n, m;
    in >> n >> m;
    vector<int> v(n + m);
    for (int i = 0; i < n + m; i++)
    {
        in >> v[i];
    }

    quicksort(v, 0, n + m - 1);
    int j = reduce(v);
    for (int i = 0; i < j; i++)
    {
        cout << v[i] << ' ';
    }

    cout << endl;
}