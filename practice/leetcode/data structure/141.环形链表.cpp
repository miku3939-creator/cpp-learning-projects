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

        set<ListNode *> s;
        bool isCycle = false;
        while (head != NULL)
        {
            if (s.find(head) == s.end())
            {
                s.insert(head);
                head=head->next;
            }
            else
            {
                isCycle = true;
                break;
            }
        }
        return isCycle;
    }
};
// @lc code=end
