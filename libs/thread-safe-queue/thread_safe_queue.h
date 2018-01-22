#ifndef THREAD_SAFE_Q_H__
#define THREAD_SAFE_Q_H__

#include <sys/types.h>

typedef char lock_t;

typedef struct thread_safe_queue {
  void **queue;
  size_t head;
  size_t tail;
  size_t size;

} thread_safe_queue;

void lock(lock_t *s);
void unlock(lock_t *s);

void init_queue(thread_safe_queue **sq, size_t q_size);
int is_empty(thread_safe_queue **sq);
int is_full(thread_safe_queue **sq);
void enqueue(thread_safe_queue **sq, void *item);
void *dequeue(thread_safe_queue **sq);

#endif
