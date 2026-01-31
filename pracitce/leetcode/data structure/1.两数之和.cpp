#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
// 暴力解法
/*
vector<int> twoSum(vector<int> &nums, int target)
{
    for (int i = 0; i < nums.size(); i++)
    {
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[i] + nums[j] == target)
            {
                return {i, j};
            }
        }
    }
    return{};
}*/
// 哈希
vector<int> twoSum(vector<int> &nums, int target)
{
    unordered_map<int, int> nummap;
    for (int i = 0; i < nums.size(); i++)
    {
        int re = target - nums[i];
        if (nummap.find(re) != nummap.end())
            return {nummap[re], i};
        else
            nummap[nums[i]] = i;
    }
    return {};
}
int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    int target;
    cin >> target;
    vector<int> res = twoSum(nums, target);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    return 0;
}