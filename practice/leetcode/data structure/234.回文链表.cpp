/*
 * @lc app=leetcode.cn id=234 lang=cpp
 *
 * [234] 回文链表
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
        // 双指针
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

    bool isPalindrome(ListNode *head)
    {
        if(!head||!head->next)
        return true;
        ListNode *fast=head;
        ListNode *slow=head;
        ListNode *newH=nullptr;
        while (fast)
        {
            if (fast->next == nullptr || fast->next->next == nullptr)
            {
                newH = slow->next;
                slow->next=nullptr;
                slow = head;
                break;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        newH = reverseList(newH);
        while (newH)
        {
            if (slow->val != newH->val)
                return false;
            slow = slow->next;
            newH = newH->next;
        }
        return true;
    }
};
// @lc code=end
