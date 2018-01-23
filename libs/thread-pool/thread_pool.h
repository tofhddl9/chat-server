#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "thread_safe_queue.h"

typedef void *(*job_t)(void *);

typedef struct thread_pool {
  thread_safe_queue *jobs;
  pthread_t *threads;
  size_t thread_num;
  
} thread_pool;

void init_thread_pool(thread_pool *tp, size_t thread_num, size_t queue_size);
void add_job_in_pool(thread_pool *tp, job_t job);
void free_thread_pool(thread_pool *tp);
void free_thread_pool_with_join(thread_pool *tp);

void *thread_work(void *pool);

#endif
