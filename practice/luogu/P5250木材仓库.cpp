#include <iostream>
#include <set>
using namespace std;
int main()
{
    int n, le;
    set<int> s;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int cho;
        cin >> cho >> le;
        switch (cho)
        {
        case 1:
        {
            if (s.find(le) == s.end())
                s.insert(le);
            else
                cout << "Already Exist" << endl;
                break;
        }
        case 2:
        {
            if (s.empty()){
                cout << "Empty" << endl;
                break;
            }
            if (s.find(le) != s.end())
            {
                cout << le << endl;
                s.erase(le);
            }
            else
            {
                s.insert(le);
                auto it = s.find(le);
                auto ot = it;
                if (it == s.begin())
                    ot++;
                else if (++it == s.end())//it指向的位置被改变了
                    ot--;
                else
                {
                    ot--;
                    if (*(ot) + *(it) < 2 * le)
                    {
                        ot = it;
                    }
                }
                cout << *(ot) << endl;
                s.erase(*(ot));
                s.erase(le);
            }
            break;
        }
        }
    }
    return 0;
}