/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */
/*
 * 基础C语言技能诊断代码。
 * 由R. E. Bryant为课程15-213/18-213/15-513开发，2017年
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */
/*
 * 该程序实现了一个支持FIFO（先进先出）和LIFO（后进先出）操作的队列。
 *
 * 它使用单向链表来表示队列元素的集合
 */
#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
/*
  创建空队列。
  如果无法分配空间，返回NULL。
*/
queue_t *q_new()
{
  /* Remember to handle the case if malloc returned NULL */
  /* 记得处理malloc返回NULL的情况 */
  queue_t *q = malloc(sizeof(queue_t));
  if (q == NULL)
    return NULL;

  q->head = NULL;
  q->tail = NULL;
  q->size = 0;
  return q;
}

/* Free all storage used by queue */
/* 释放队列使用的所有存储空间 */
void q_free(queue_t *q)
{
  /* Remember to free the queue structue and list elements */
  /* 记得释放队列结构和链表元素 */
  if (q == NULL)
    return;
  list_ele_t *p = q->head;
  while (p != NULL)
  {
    list_ele_t *temp = p->next;
    free(p);
    p = temp;
  }
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
/*
  尝试在队列头部插入元素。
  如果成功返回true。
  如果q为NULL或无法分配空间，返回false。
*/
bool q_insert_head(queue_t *q, int v)
{
  /* What should you do if the q is NULL? */
  /* What if malloc returned NULL? */
  /* 如果q为NULL应该怎么做？ */
  /* 如果malloc返回NULL怎么办？ */
  if (q == NULL)
    return false;
  list_ele_t *p = malloc(sizeof(list_ele_t));
  if (p == NULL)
    return false;
  p->value = v;
  if (q->head == NULL)
  {
    q->head = p;
    q->tail = p;
    p->next = NULL;
  }
  else
  {
    p->next = q->head;
    q->head = p;
  }
  q->size++;
  return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
/*
  尝试在队列尾部插入元素。
  如果成功返回true。
  如果q为NULL或无法分配空间，返回false。
*/
bool q_insert_tail(queue_t *q, int v)
{
  /* Remember: It should operate in O(1) time */
  /* 记住：操作应该在O(1)时间内完成 */
  if (q == NULL)
    return false;
  list_ele_t *p = malloc(sizeof(list_ele_t));
  if (p == NULL)
    return false;
  p->value = v;
  p->next = NULL;
  if (q->head == NULL)
    q->head = p;
  else
    q->tail->next = p;
  q->tail = p;
  q->size++;
  return true;
}
/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
/*
  尝试从队列头部移除元素。
  如果成功返回true。
  如果队列为NULL或为空，返回false。
  如果vp非NULL且元素被成功移除，将移除的值存储在*vp中。
  任何不再使用的存储空间都应该被释放
*/
bool q_remove_head(queue_t *q, int *vp)
{
  if (q == NULL)
    return false;
  if (q->head == NULL)
    return false;
    if(vp!=NULL)
  *vp = q->head->value;
  list_ele_t *temp = q->head->next;
  free(q->head);
  q->head = temp;
  q->size--;
  if (q->head == NULL)
    q->tail = NULL;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
/*
  返回队列中元素的数量。
  如果q为NULL或队列为空，返回0
*/
int q_size(queue_t *q)
{
  /* Remember: It should operate in O(1) time */
  /* 记住：操作应该在O(1)时间内完成 */
  if (q == NULL || q->head == NULL)
    return 0;
  return q->size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
/*
  反转队列中的元素。

  你的实现不能分配或释放任何元素（例如，通过调用q_insert_head或q_remove_head）。
  相反，它应该修改现有数据结构中的指针。
*/
void q_reverse(queue_t *q)
{
  if (q == NULL || q->head == NULL)
    return;

  list_ele_t *prev = NULL;
  list_ele_t *curr = q->head;
  list_ele_t *next = NULL;

  while (curr != NULL)
  {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  q->tail = q->head;
  q->head = prev;
}
