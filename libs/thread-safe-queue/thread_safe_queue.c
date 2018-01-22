#include <stdlib.h>

#include "thread_safe_queue.h"

void lock(thread_safe_queue *sq)
{
  while (__atomic_compare_exchange(&(sq->_lock), &(sq->expected),
    &(sq->desired), 1, __ATOMIC_RELAXED, __ATOMIC_RELAXED) == 0);
}

void unlock(thread_safe_queue *sq)
{
  __atomic_store(&sq->_lock, &(sq->expected), __ATOMIC_RELAXED);
}

void init_queue(thread_safe_queue *sq, size_t q_size)
{
  sq->size = q_size;
  sq->head = 0;
  sq->tail = 0;
  sq->_lock = 0;
  sq->expected = 0;
  sq->desired = 1;
}

char is_empty(thread_safe_queue *sq)
{
  char ret;
  lock(sq);
  if (sq->head == sq->tail)
    ret = 1;
  else
    ret = 0;
  unlock(sq);

  return ret;
}

char is_full(thread_safe_queue *sq)
{
  char ret;
  lock(sq);
  if (sq->head == (sq->tail+1 % sq->size))
    ret = 1;
  else
    ret = 0;
  unlock(sq);

  return ret;
}

char enqueue(thread_safe_queue *sq, void *job)
{
  char ret = is_full(sq);
  lock(sq);
  if (ret == 0)
    sq->queue[(sq->tail++) % sq->size] = job;
  else
    ret = -1;
  unlock(sq);

  return ret;
}

void *dequeue(thread_safe_queue *sq)
{
  void *job = NULL;
  int ret = is_empty(sq);
  lock(sq);
  if (ret == 0) {
    job = sq->queue[sq->head];
    sq->head = (++sq->head) % sq->size;
  }
  unlock(sq);

  return job;
}
