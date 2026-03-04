/*  Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017*/

/* This program implements a queue supporting both FIFO and LIFO operations.
 It uses a singly-linked list to represent the set of queue elements*/

#include <stdbool.h>

/************** Data structure declarations ****************/
/************** 数据结构声明 ****************/

/* Linked list element (You do not need to change this but you may.) */
/* 链表元素（你可以不修改这个结构，但也可以修改） */
typedef struct ELE {
    int value;               /* 元素的值 */
    struct ELE *next;        /* 指向下一个元素的指针 */
} list_ele_t;

/* Queue structure */
/* 队列结构 */
typedef struct {
    list_ele_t *head;        /* Linked list of elements */
                             /* 元素的链表 */
    /*
      You will need to add more fields to this structure
      to efficiently implement q_size and q_insert_tail
    */
    /*
      你需要在这个结构中添加更多字段
      以高效地实现 q_size 和 q_insert_tail
    */
   list_ele_t *tail;
   int size;
} queue_t;

/************** Operations on queue ************************/
/************** 队列操作 ************************/

/*
  Create empty queue.
  Return NULL if could not allocate space.
  创建空队列。
  如果无法分配空间，返回NULL。
*/
queue_t *q_new();

/*
  Free all storage used by queue.
  No effect if q is NULL
  释放队列使用的所有存储空间。
  如果q为NULL，不进行任何操作。
*/
void q_free(queue_t *q);

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  尝试在队列头部插入元素。
  如果成功返回true。
  如果q为NULL或无法分配空间，返回false。
*/
bool q_insert_head(queue_t *q, int v);

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  尝试在队列尾部插入元素。
  如果成功返回true。
  如果q为NULL或无法分配空间，返回false。
*/
bool q_insert_tail(queue_t *q, int v);

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
  尝试从队列头部移除元素。
  如果成功返回true。
  如果队列为NULL或为空，返回false。
  如果vp非NULL且元素被成功移除，将移除的值存储在*vp中。
  任何不再使用的存储空间都应该被释放。
*/
bool q_remove_head(queue_t *q, int *vp);

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
  返回队列中元素的数量。
  如果q为NULL或队列为空，返回0。
*/
int q_size(queue_t *q);

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  反转队列中的元素。
  如果q为NULL或队列为空，不进行任何操作。
*/
void q_reverse(queue_t *q);
/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdbool.h>

/************** Data structure declarations ****************/

/* Linked list element (You do not need to change this but you may.) */
typedef struct ELE {
    int value;
    struct ELE *next;
} list_ele_t;

/* Queue structure */
typedef struct {
    list_ele_t *head;        /* Linked list of elements */
    /*
      You will need to add more fields to this structure
      to efficiently implement q_size and q_insert_tail
    */
    list_ele_t *tail;
    int size;
} queue_t;

/************** Operations on queue ************************/

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new();

/*
  Free all storage used by queue.
  No effect if q is NULL
*/
void q_free(queue_t *q);

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v);

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v);

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp);

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q);

/*
  Reverse elements in queue
  No effect if q is NULL or empty
 */
void q_reverse(queue_t *q);