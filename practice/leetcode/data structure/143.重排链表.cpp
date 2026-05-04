/*
 * @lc app=leetcode.cn id=143 lang=cpp
 *
 * [143] 重排链表
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution
{
public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode *prev = NULL;
        ListNode *curr = head;
        while (curr != NULL)
        {
            ListNode *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
    void reorderList(ListNode *head)
    {
        if(!head||!head->next)return;
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast->next != NULL&&fast->next->next != NULL)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
       
        fast = reverseList(slow->next);
        slow->next = NULL;
         slow = head;
        while (slow != NULL && fast != NULL)
        {
            ListNode *temp1 = slow->next;
            ListNode *temp2 = fast->next;
            slow->next = fast;
            slow = temp1;
            fast->next = slow;
            fast = temp2;
        }
        return ;
    }
};
// @lc code=end
