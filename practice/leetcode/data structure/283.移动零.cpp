/*
 * @lc app=leetcode.cn id=283 lang=cpp
 *
 * [283] 移动零
 */

// @lc code=start
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n=nums.size(),left=0,right =0;
       /*1 for(int i=n;i>0;i--){
            for(int j=1;j<i;j++){
               if(nums[j-1]==0)
               swap(nums[j-1],nums[j]);
            }
        }*/
       while(right<n){
        if(nums[right]){
         swap(nums[left],nums[right]);
         left++;
        }
        right++;
       }

    }
};
// @lc code=end

