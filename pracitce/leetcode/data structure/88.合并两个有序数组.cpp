/*
 * @lc app=leetcode.cn id=88 lang=cpp
 *
 * [88] 合并两个有序数组
 */

// @lc code=start
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n==0){
            return;
        }
        if(m==0){
            for(int i=0;i<n;i++){
                nums1[i]=nums2[i];
            }
            return;
        }
        /*1
        for(int i=m;i<m+n;i++){
            nums1[i]=nums2[i-m];
        }
        sort(nums1.begin(),nums1.end());*/
        int i=m+n-1;
        m--;
        n--;
        while(n>=0){
            if(m>=0&&nums1[m]>nums2[n]){
                swap(nums1[i],nums1[m]);
                m--;
            }
            else{
                swap(nums1[i],nums2[n]);
             n--;
            }
              i--;
        }
      
    }
};
// @lc code=end

