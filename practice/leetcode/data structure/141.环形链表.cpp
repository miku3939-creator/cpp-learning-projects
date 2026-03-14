/*
 * @lc app=leetcode.cn id=141 lang=cpp
 *
 * [141] 环形链表
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
    bool hasCycle(ListNode *head)
    {

        /*1unordered_set<ListNode *> s;
        while (head != NULL)
        {
            if (s.find(head) != s.end())
                return true;
            s.insert(head);
            head = head->next;
        }
        return false;*/
        if(head==NULL||head->next==NULL)
        return false;
        ListNode * slow=head;
        ListNode * fast=head->next;
        while(fast!=NULL&&fast->next!=NULL){
            if(slow==fast)
            return true;
            slow=slow->next;
            fast=fast->next->next;
        }
        return false;
    }
};
// @lc code=end
