#include <iostream>
using namespace std;
// 头节点不存数据
void sort()
{
    Node *p, *pre, *q;
    q = head->next;
    // 表空
    if (q == NULL)return;
    p = head->next->next;
    // 只有一个数据
    if (p == NULL)return;
    //此表只有第一个数据
    q->next=NULL;
    while(p!=NULL){
        q=p->next;
        pre=head;
        while(pre->next!=NULL&&pre->next->exp>p->exp)
        pre=pre->next;
        p->next=pre->next;
        pre->next=p;
        p=q;
    }
}