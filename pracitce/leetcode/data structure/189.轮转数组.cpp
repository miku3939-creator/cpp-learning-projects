/*
 * @lc app=leetcode.cn id=189 lang=cpp
 *
 * [189] 轮转数组
 */

// @lc code=start

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        //my way
        /*int j=nums.size();
        if(k>j){
            k%=j;
        }
        if(k==0)
        return ;
        
        for(int i=0;i<j;i++){
            nums.push_back(nums[i]);
        }
          for(int i=0;i<j;i++){
            nums[i]=nums[i+j-k];
        }
        while(j){
            nums.pop_back();
            j--;
        }*/

        //better
        nums.reverse(nums.end()-k,nums.end());
        nums.reverse(nums.begin(),nums.end()-k);
        nums.reverse(nums.begin(),nums.end());
    }
};
// @lc code=end

