#ifndef THREAD_SAFE_Q_H__
#define THREAD_SAFE_Q_H__

#include <sys/types.h>

typedef struct thread_safe_queue {
  void **queue;
  size_t head;
  size_t tail;
  size_t size;
  char _lock;
  char expected;
  char desired;

} thread_safe_queue;

void lock(thread_safe_queue *sq);
void unlock(thread_safe_queue *sq);

void init_queue(thread_safe_queue *sq, size_t q_size);
char is_empty(thread_safe_queue *sq);
char is_full(thread_safe_queue *sq);
char enqueue(thread_safe_queue *sq, void *item);
void *dequeue(thread_safe_queue *sq);

#endif
