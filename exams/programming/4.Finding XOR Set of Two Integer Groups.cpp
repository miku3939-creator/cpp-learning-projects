/*【问题描述】

从标准输入中输入两组整数(每行不超过20个整数，每组整数中元素不重复),合并两组整数，去掉在两组整数中都出现的整数，并按从大到小顺序排序输出（即两组整数集"异或"）。

【输入形式】

首先输入第一组整数，以一个空格分隔各个整数；然后在新的一行上输入第二组整数，以一个空格分隔，行末有回车换行。

【输出形式】

按从大到小顺序排序输出合并后的整数集（去掉在两组整数中都出现的整数，以一个空格分隔各个整数）。

【样例输入】

5 1 4 32 8 7 9 -6
5 2 87 10 1
【样例输出】

87 32 10 9 8 7 4 2 -6
【样例说明】

第一组整数为5   1   4   32   8   7   9   -6，
第二组整数分别为5   2   87   10   1。将第一组和第二组整数合并（去掉在两组整数中都出现的整数5和1），
并从大到小顺序排序后结果为87   32   10   9   8   7   4   2   -6。
*/

/*#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    vector<int> v;
    int e;
    bool single = true;
    stringstream ss(s1);
    string temp;
    while (ss >> temp)
    {
        e = stoi(temp);

        v.push_back(e);
    }

    stringstream s(s2);

    while (s >> temp)
    {
        e = stoi(temp);
        for (vector<int>::iterator i = v.begin(); i < v.end(); i++)
        {
            if (e == (*i))
            {
                single = false;
                i=v.erase(i);
            }
        }
        if (single == true)
            v.push_back(e);

        single = true;
    }
    sort(v.begin(), v.end(),greater());
    for (auto &e : v)
    {
        cout << e << ' ';
    }
    return 0;
}*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include<sstream>

using namespace std;

/*bool myCompare(const int v1, const int v2)
 {
     return v1 > v2;
 }*/

void reset(string &s, vector<int> &n)
{
    stringstream ss(s);
    int temp;
   while( ss>>temp){
    n.push_back(temp);
   }
    
   /* int l = 0;
    int r = s.find(' ', l + 1);
    int c;
    while (l != -1)
    {
        c = stoi(s.substr(l, r - l + 1));
        n.push_back(c);
        l = r;
        r = s.find(' ', r + 1);
    }*/

}

int main()
{
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    vector<int> num;
    reset(s1, num);
    reset(s2, num);
        if (num.empty())
        return 0;
    vector<int> v;
    int n = num.size();
    sort(num.begin(), num.end(), greater<int>());
    for (int i = 0; i < n;)
    {
        if (i == n - 1)
        {
            v.push_back(num[i]);
            break;
        }
        if (num[i] == num[i + 1])
        {
            i += 2;
        }
        else
        {
            v.push_back(num[i]);
            i++;
        }
    }
    if (v.empty())
        return 0;
    for (auto &n : v)
    {
        cout << n << ' ';
    }
    return 0;
}