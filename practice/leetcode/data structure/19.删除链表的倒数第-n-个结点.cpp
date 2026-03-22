/*
 * @lc app=leetcode.cn id=19 lang=cpp
 *
 * [19] 删除链表的倒数第 N 个结点
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
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
        /*false way:
        if (head->next == NULL)
        {
            delete head;
            return NULL;
        }
        unordered_map<int, ListNode *> m;
        int i = 0;
        while (head != NULL)
        {
            m[i] = head;
            head = head->next;
            i++;
        }
        auto it = m.find(i - n);
        if (n == 1)
        {
            delete it->second->next;
            it->second->next = NULL;
            it = m.find(0);
            return it->second;
        }
        it->second->next = it->second->next->next;
        it = m.find(i + 1 - n);
        delete it->second;
        it = m.find(0);
        return it->second;*/

        /*2if (head->next == NULL)
        {
            delete head;
            return NULL;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        int i = 0;
        while (fast != NULL)
        {
            i++;
            fast = fast->next;
        }
        i=i-n-1;
        if(i<0){
            slow=head->next;
            delete head;
            return slow;
        }
        while(i>0){
            i--;
            slow=slow->next;
        }
        fast=slow->next;
        slow->next=slow->next->next;
        delete fast;
        return head;*/
        if (head->next == NULL)
        {
            delete head;
            return NULL;
        }
        ListNode *slow = head;
        ListNode *fast = head;
        n += 1;
        while (n > 0)
        {
            if (fast == NULL)
            {
                slow = head->next;
                delete head;
                return slow;
            }
            n--;
            fast = fast->next;
        }
        while (fast != NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
        fast = slow->next;
        slow->next = slow->next->next;
        delete fast;
        return head;
    }
    /*best!!!!
          ListNode* dummy=new ListNode(0,head);
        ListNode *slow = dummy;
        ListNode *fast = dummy;
        while (n >= 0)
        {
          fast=fast->next;
          n--;
        }
        while (fast!= NULL)
        {
            fast = fast->next;
            slow = slow->next;
        }
        fast= slow->next;
        slow->next = fast->next;
        delete fast;
        fast= dummy->next;
        delete dummy;
        return fast;*/
};
// @lc code=end
