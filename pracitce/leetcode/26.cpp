#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;
int removeDuplicates(vector<int> &nums)
{
    
    vector<int> b;
    for (auto &e : nums)
    {bool isok = true;
        for (auto &f : b)
        {
            if (f == e)
            {
                isok = false;
                 break;
            }
           
        }

        if (isok)
            b.push_back(e);
    }
    int n = b.size();
    for (int i = 0; i < n; i++)
    {
        nums[i] = b[i];
    }
    return n;
}

int main()
{
    vector<int> nums;
    string num;
    getline(cin, num);
    stringstream ss(num);
    string c;
    while (ss >> c)
    {
        nums.push_back(stoi(c));
    }
    int k=removeDuplicates(nums); // 调用
    for (int i = 0; i < k; i++)
    {
        cout << nums[i]<<' ';
    }
    return 0;
}