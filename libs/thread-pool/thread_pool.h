#include <sys/types.h>

#include <pthread.h>
#include "../thread-safe-queue/thread_safe_queue.h"

typedef void *(*job_t)(void *);

typedef struct thread_pool {
  thread_safe_queue jobs;
  pthread_t *threads;
  size_t thread_num;
  
} thread_pool;

thread_pool *create_thread_pool(size_t thread_num, size_t queue_size);
void add_job_in_pool(thread_pool *tp, job_t func);

void *thread_work(void *pool);
