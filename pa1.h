#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
#ifndef SOME_HEADER_GUARD_WITH_UNIQUE_NAME
#define SOME_HEADER_GUARD_WITH_UNIQUE_NAME
typedef struct{
  int arrival_time;
  int burst_time;
  int priority_level;
  int remaining_time;
  int tt;
}process;
typedef struct node{
  struct node* next;
  process value;
}node;
typedef struct queue2{
    node* head;
    node* tail;
    int size;
}lnklst_queue;
typedef struct{
  int* data;
  int size;
  unsigned capacity;
} heap;
typedef struct{
    process* data;
    int size;
    unsigned capacity;
} heap2;
#endif
//linked list queue
lnklst_queue create_queue2();
int is_full2(lnklst_queue);
int is_empty2(lnklst_queue);
void enqueue2(lnklst_queue*, process);
process dequeue2(lnklst_queue*);
process front2(lnklst_queue);
process rear2(lnklst_queue);
//max or min heap
heap create_heap(unsigned);
heap clone(heap h);
int is_empty(heap);
int is_full(heap);
void clear(heap*);
void max_insert(heap*, int);
int max_delete(heap*);
int get_max(heap);
void min_insert(heap*, int);
int min_delete(heap*);
int get_min(heap);
//SJF min heap
//max or min heap
heap2 create_heap2(unsigned);
heap2 clone2(heap2 h);
int is_empty3(heap2);
int is_full3(heap2);
void clear2(heap2*);
void max_insert2(heap2*, int);
int max_delete2(heap2*);
int get_max2(heap2);
void min_insert2(heap2*, process*);
process min_delete2(heap2*);
int get_min2(heap2);
