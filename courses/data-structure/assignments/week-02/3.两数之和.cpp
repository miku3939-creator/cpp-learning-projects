#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <fstream>
using namespace std;
class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> m;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (m.find(target - nums[i]) == m.end())
                m[nums[i]] = i;
            else
            {
                return {m.find(target - nums[i])->second, i};
            }
        }
        return {-1, -1};
    }
};
int main()
{
    ifstream in("in.txt");
    if (!in.is_open())
    {
        cerr << "无法打开 in.txt" << endl;
        return 0;
    }
    string line;
    getline(in, line);
    vector<int> nums;
    stringstream ss(line);
    int temp;
    while (ss >> temp)
    {
        nums.push_back(temp);
    }
    int target;
    in>> target;
    Solution s;
    vector<int> res = s.twoSum(nums, target);
    for (int i = 0; i < 2; i++)
    {
        cout << res[i];
        if (i==0)
            cout << " ";
    }
    cout << endl;
    return 0;
}