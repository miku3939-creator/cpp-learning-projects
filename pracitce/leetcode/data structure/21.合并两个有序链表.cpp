/*
 * @lc app=leetcode.cn id=21 lang=cpp
 *
 * [21] 合并两个有序链表
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
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode temp(0);
        ListNode *res = &temp;
        while (list1 != NULL && list2 != NULL)
        {
            if (list1->val < list2->val)
            {
                res->next = list1;
                res = res->next;
                list1 = list1->next;
            }
            else
            {
                res->next = list2;
                res = res->next;
                list2 = list2->next;
            }
        }
        while (list1 != NULL)
        {
            res->next = list1;
            res = res->next;
            list1 = list1->next;
        }
        while (list2 != NULL)
        {
            res->next = list2;
            res = res->next;
            list2 = list2->next;
        }
        return temp.next;
    }
};
// @lc code=end
