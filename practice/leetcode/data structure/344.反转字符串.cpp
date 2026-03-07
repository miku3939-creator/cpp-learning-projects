/*
 * @lc app=leetcode.cn id=344 lang=cpp
 *
 * [344] 反转字符串
 */

// @lc code=start
class Solution {
public:
    void reverseString(vector<char>& s) {
        int j=s.size()-1;
        int i=0;
        int temp;
        /*for(int i=0;i<j;i++){
swap(s[i],s[n-i]);
        }*/
       while(j-i>0){
        temp=s[j];
        s[j]=s[i];
        s[i]=temp;
        j--;i++;
       }
    }
};
// @lc code=end

