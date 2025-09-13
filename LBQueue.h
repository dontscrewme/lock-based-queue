#ifndef _LOCKBASED_QUEUE_H_
#define _LOCKBASED_QUEUE_H_
#include "queue.h"
#include <pthread.h>

void LBQueue_set_error_callback(int (*errback)(const char *, ...));


struct LBQueue
{
  struct queue queue;
  pthread_mutex_t mutex;
};

int LBQueue_init(struct LBQueue* me);
void LBQueue_destroy(struct LBQueue* me);
int enqueueLB(struct LBQueue* me, int data);
int dequeueLB(struct LBQueue* me, int* out);
#endif