#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
int main()
{
    ifstream in("in.txt");
    string line, res = "";
    getline(in, line);
    stringstream ss(line);
    char e;
    while (ss >> e)
    {
        res += e;
    }
    int read = 0, write = 0;
    int n = res.size();
    if (n <= 1)
    {
        cout << res << endl;
        return 0;
    }
    while (read < n)
    {
        int start = read;
        while (read < n && res[read] == res[start])
        {
            read++;
        }
        res[write++] = res[start];
        int count = read - start;
        if (count > 1)
        {
            string s = to_string(count);
            for (char c : s)
            {
                res[write++] = c;
            }
        }
    }
    for (int i = 0; i < write; i++)
    {
        cout << res[i] << ' ';
    }
    cout << endl;
    return 0;
}