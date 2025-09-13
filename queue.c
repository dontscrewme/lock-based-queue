#include "queue.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

static int default_error_callback(const char *format, ...) {
  int ret;
  va_list argptr;
  va_start(argptr, format);
  ret = vfprintf(stderr, format, argptr);
  va_end(argptr);
  return ret;
}

int (*queue_error_callback)(const char *, ...) = default_error_callback;

void queue_set_error_callback(int (*errback)(const char *, ...)) {
  if (errback) {
    queue_error_callback = errback;
  }
}

int queue_init(struct queue* q)
{
  if (q == NULL)
  {
    queue_error_callback("%s: invalid input\n", __func__);
    return -1;
  }

  struct queue_node* dummy = malloc(sizeof(*dummy));
  if (dummy == NULL)
  {
    queue_error_callback("%s: malloc() failed\n", __func__);
    return -1;
  }

  dummy->next = NULL;
  q->tail = dummy;
  q->head = dummy;

  return 0;
}

void queue_destroy(struct queue* q)
{
  if (q == NULL)
  {
    queue_error_callback("%s: invalid input\n", __func__);
    return;
  }

  struct queue_node* current = q->head;
  while (current != NULL)
  {
    struct queue_node* node_to_free = current;
    current = current->next;
    free(node_to_free);
  }

  q->head = q->tail = NULL;

  return;
}


int enqueue(struct queue* q, int data)
{
  if (q == NULL)
  {
    queue_error_callback("%s: invalid input\n", __func__);
    return -1;
  }

  struct queue_node* new_node = malloc(sizeof(*new_node));
  if (new_node == NULL)
  {
    queue_error_callback("%s: malloc() failed\n", __func__);
    return -1;
  }

  new_node->data = data;
  new_node->next = NULL;

  q->tail->next = new_node;
  q->tail = new_node;

  return 0;
}

int dequeue(struct queue* q, int* out)
{
  struct queue_node* dummy = q->head;
  if (dummy->next == NULL)
  {
    return -1;
  }

  q->head = dummy->next;
  *out = q->head->data;
  free(dummy);

  return 0;
}
