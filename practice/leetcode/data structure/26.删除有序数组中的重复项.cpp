/*
 * @lc app=leetcode.cn id=26 lang=cpp
 *
 * [26] 删除有序数组中的重复项
 */

// @lc code=start
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        // my answer
        /*set<int> res;
        for (auto e: nums)
        {
            res.insert(e);
        }
        nums.assign(res.begin(),res.end());
        return res.size();*/

        // better快慢指针
        if (nums.empty())
            return 0;
        int i = 0;
        for (int j = 1; j < nums.size(); j++)
        {
            if (nums[j] != nums[i])
            {
                i++;
                nums[i] = nums[j];
            }
        }
        return i + 1;
    }
};
// @lc code=end
