#include <sys/types.h>
#include <pthread.h>

typedef struct thread_safe_queue {
  void *queue;
  size_t head;
  size_t tail;
  size_t size;

} thread_safe_queue;

thread_safe_queue *create_queue (size_t element_size, size_t q_size);
int is_empty(thread_safe_queue *sq);
int is_full(thread_safe_queue *sq);
void enqueue(thread_safe_queue *sq, void *item);
void *dequeue(thread_safe_queue *sq);
