#include <iostream>
#include <vector>
using namespace std;
int main()
{
    int a, x, n, sum, res;
    cin >> a >> n >> sum >> res;
    x = 1;
    if(res==1)
    {
        cout<<a;
        return 0;
    }
    vector<int> add(n);
    vector<int> s(n);
    vector<int>a2(n);
    vector<int>s2 (n);
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            add[i] = a;
            s[i] = a;
        }
        else if (i == 1)
        {
            add[i] = x;
            s[i] = a;
        }
        else
        {
            add[i] = add[i - 1] + add[i - 2];
            s[i] = s[i - 1] + add[i - 2];
        }
    }
      for (int i = 0; i < n-1; i++)
    {
        if (i == 0)
        {
            a2[i] = a;
            s2[i] = a;
        }
        else if (i == 1)
        {
            a2[i] = 0;
            s2[i] = a;
        }
        else
        {
            a2[i] = a2[i - 1] + a2[i - 2];
            s2[i] = s2[i - 1] + a2[i - 2];
        }
    }
int y=s[n-2]-s2[n-2];
x=(sum-s2[n-2])/y;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            add[i] = a;
            s[i] = a;
        }
        else if (i == 1)
        {
            add[i] = x;
            s[i] = a;
        }
        else
        {
            add[i] = add[i - 1] + add[i - 2];
            s[i] = s[i - 1] + add[i - 2];
        }
    }
    cout<<s[res-1]<<endl;
return 0;
}
