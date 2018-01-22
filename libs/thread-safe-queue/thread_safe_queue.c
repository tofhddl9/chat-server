#include <stdlib.h>
#include <pthread.h>

#include "thread_safe_queue.h"

lock_t val = 0;
lock_t expected = 0;
lock_t desired = 1;

void lock(lock_t *val)
{
  while (__atomic_compare_exchange(val, &expected, &desired,
    1, __ATOMIC_RELAXED, __ATOMIC_RELAXED) != 0);
}

void unlock(lock_t *val)
{
  __atomic_sub_fetch(val, 1, __ATOMIC_RELAXED);
}

void init_queue(thread_safe_queue **sq, size_t q_size)
{
  (*sq)->size = q_size;
  (*sq)->head = 0;
  (*sq)->tail = 0;
}

int is_empty(thread_safe_queue **sq)
{
  if ((*sq)->head == (*sq)->tail)
    return 1;
  return 0;
}

int is_full(thread_safe_queue **sq)
{
  if ((*sq)->head == (((*sq)->tail+1) % (*sq)->size))
    return 1;
  return 0;
}

void enqueue(thread_safe_queue **sq, void *job)
{
  int ret = is_full(sq);
  lock(&val);
  if (ret == 0) {
    (*sq)->queue[((*sq)->tail++)%(*sq)->size] = job;
  }
  //else error
  unlock(&val);
}

void *dequeue(thread_safe_queue **sq)
{
  void *job;
  int ret = is_empty(sq);
  lock(&val);
  if (ret == 0) {
    job = (*sq)->queue[(*sq)->head];
    (*sq)->head = (++(*sq)->head) % (*sq)->size;
  }
  unlock(&val);
  return job;
}
