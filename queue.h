#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdio.h>

#include "queue.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

struct queue_node
{
  int data;
  struct queue_node* next;
};

struct queue
{
  struct queue_node* head;
  struct queue_node* tail; 
};

int queue_init(struct queue* q);
void queue_destroy(struct queue* q);
int enqueue(struct queue* q, int data);
int dequeue(struct queue* q, int* out);


extern int (*queue_error_callback)(const char *, ...);
void queue_set_error_callback(int (*errback)(const char *, ...));

#endif