#include <sys/types.h>

typedef void *(*job_t)(void *);

typedef struct thread_safe_queue {
  job_t *queue;
  int head;
  int tail;
  size_t size;

} thread_safe_queue;

thread_safe_queue *create_queue (size_t size);
int is_empty(thread_safe_queue *sq);
int is_full(thread_safe_queue *sq);
void enqueue(thread_safe_queue *sq, job_t job);
job_t dequeue(thread_safe_queue *sq);