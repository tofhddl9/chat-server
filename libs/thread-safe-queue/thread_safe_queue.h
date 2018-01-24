#ifndef THREAD_SAFE_Q_H__
#define THREAD_SAFE_Q_H__

#include <sys/types.h>

typedef struct thread_safe_queue {
  char *queue;
  size_t head;
  size_t tail;
  size_t queue_size;
  size_t element_size;
  char _lock;

} thread_safe_queue;

void lock(char *sq);
void unlock(char *sq);

void init_queue(thread_safe_queue *sq, size_t e_size, size_t q_size);
char is_empty(thread_safe_queue *sq);
char is_full(thread_safe_queue *sq);
char enqueue(thread_safe_queue *sq, char *item);
char dequeue(thread_safe_queue *sq, char *out);

#endif
