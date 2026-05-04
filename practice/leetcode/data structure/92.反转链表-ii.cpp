/*
 * @lc app=leetcode.cn id=92 lang=cpp
 *
 * [92] 反转链表 II
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
    vector<ListNode *>reverseList(ListNode *head, int n)
    {
        ListNode *pre = NULL;
        ListNode *p = head;
        while (n != 0)
        {
            ListNode *next = p->next;
            p->next = pre;
            pre = p;
            p = next;
            n--;
        }
        return {head,pre,p};
    }
    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        int n = right - left + 1;
        ListNode *dummy=new ListNode(-1,head);
        ListNode *p=dummy;
        ListNode *ripre=NULL;
        vector<ListNode*> v;
        for(int i=0;i<=left;i++){
            if(i==left-1)
            ripre=p;
            if(i==left)
            v=reverseList(p,n);
            p=p->next;
        }
        ripre->next=v[1];
        v[0]->next=v[2];
        return dummy->next;
    }
};
// @lc code=end
