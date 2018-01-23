#include <stdlib.h>

#include "thread_safe_queue.h"

void lock(char *val)
{
  while (!__atomic_test_and_set(val, __ATOMIC_RELAXED));
}

void unlock(char *val)
{
  __atomic_clear(val, __ATOMIC_RELAXED);
}

void init_queue(thread_safe_queue *sq, size_t q_size)
{
  sq->size = q_size;
  sq->head = 0;
  sq->tail = 0;
  sq->_lock = 0;
}

char is_empty(thread_safe_queue *sq)
{
  char ret;
  lock(&sq->_lock);
  if (sq->head == sq->tail)
    ret = 1;
  else
    ret = 0;
  unlock(&sq->_lock);

  return ret;
}

char is_full(thread_safe_queue *sq)
{
  char ret;
  lock(&sq->_lock);
  if (sq->head == ((sq->tail+1) % sq->size))
    ret = 1;
  else
    ret = 0;
  unlock(&sq->_lock);

  return ret;
}

char enqueue(thread_safe_queue *sq, void *job)
{
  char ret = is_full(sq);
  lock(&sq->_lock);
  if (ret == 0) {
    sq->queue[sq->tail] = job;
    sq->tail = ((sq->tail+1) % sq->size);
  }
  else
    ret = -1;
  unlock(&sq->_lock);
  return ret;
}

void *dequeue(thread_safe_queue *sq)
{
  void *job = NULL;
  int ret = is_empty(sq);
  lock(&sq->_lock);
  if (ret == 0) {
    job = sq->queue[sq->head];
    sq->head = (((sq->head) + 1) % sq->size);
  }
  unlock(&sq->_lock);

  return job;
}
