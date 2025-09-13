#include "LBQueue.h"
#include <stdlib.h>

void LBQueue_set_error_callback(int (*errback)(const char *, ...))
{
  queue_set_error_callback(errback);
}


int LBQueue_init(struct LBQueue* me)
{
  if (me == NULL)
  {
    return -1;
  }

  if (queue_init(&me->queue) == -1)
  {
    return -1;
  }

  if (pthread_mutex_init(&me->mutex, NULL) != 0) {
    queue_error_callback("%s: mutex_init failed\n", __func__);
    queue_destroy(&me->queue);
    return -1;
  }
  
  return 0;
}

void LBQueue_destroy(struct LBQueue* me)
{
  if (me == NULL)
  {
    return;
  }

  queue_destroy(&me->queue);
  pthread_mutex_destroy(&me->mutex);
}

int enqueueLB(struct LBQueue* me, int data)
{
  if (me == NULL)
  {
    queue_error_callback("%s: invalid input\n", __func__);
    return -1;
  }

  pthread_mutex_lock(&me->mutex);
  
  int ret = enqueue(&me->queue, data);
  if (ret != 0)
  {
    pthread_mutex_unlock(&me->mutex);
    return ret;
  }

  pthread_mutex_unlock(&me->mutex);
  return ret;
}

int dequeueLB(struct LBQueue* me, int* out)
{
  if (me == NULL || out == NULL)
  {
    queue_error_callback("%s: invalid input\n", __func__);
    return -1;
  }

  pthread_mutex_lock(&me->mutex);

  int ret = dequeue(&me->queue, out);
  if (ret != 0) {
    pthread_mutex_unlock(&me->mutex);
    return ret;
  }
  
  pthread_mutex_unlock(&me->mutex);
  return ret;
}