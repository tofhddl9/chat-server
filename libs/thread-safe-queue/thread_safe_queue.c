#include <stdlib.h>
#include <string.h>

#include "thread_safe_queue.h"


void lock(char *val)
{
  while (!__atomic_test_and_set(val, __ATOMIC_RELAXED));
}

void unlock(char *val)
{
  __atomic_clear(val, __ATOMIC_RELAXED);
}

void init_queue(thread_safe_queue *sq, size_t e_size, size_t q_size)
{
  sq->queue = (char *)malloc(e_size * q_size);
  sq->queue_size = q_size;
  sq->element_size = e_size;
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
  if (sq->head == sq->tail)
    ret = 1;
  else
    ret = 0;
  unlock(&sq->_lock);

  return ret;
}

char enqueue(thread_safe_queue *sq, char *item)
{
  char ret = is_full(sq);
  lock(&sq->_lock);
  if (ret == 0) {
    memcpy(sq->queue[sq->tail * sq->element_size], item, sq->element_size);
    sq->tail = (sq->tail + 1) % sq->queue_size;
  }
  unlock(&sq->_lock);
  // if (ret != 0) throw error
  return ret;
}

char dequeue(thread_safe_queue *sq, char *out)
{
  char ret = is_empty(sq);
  lock(&sq->_lock);
  if (ret == 0) {
    memcpy(out, sq->queue[sq->head * sq->element_size], sq->element_size);
    sq->head = (sq->head + 1) % sq->queue_size;
  }
  unlock(&sq->_lock);
  // if (ret != 0) throw error
  return ret;
}
