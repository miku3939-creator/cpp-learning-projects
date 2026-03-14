/*
 * @lc app=leetcode.cn id=160 lang=cpp
 *
 * [160] 相交链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        /* unordered_set<ListNode*>s;
         while(headA!=NULL){
             s.insert(headA);
             headA=headA->next;
         }
         while(headB!=NULL){
             if(s.find(headB)!=s.end())
             return headB;
             headB=headB->next;
         }
         return NULL;*/
        if (!headA || !headB)
            return nullptr;
        ListNode *pa = headA;
        ListNode *pb = headB;
        while (pa != pb)
        {
            pa = pa ? pa->next : headB;
            pb = pb ? pb->next : headA;
        }
        return pa;
    }
};
// @lc code=end
