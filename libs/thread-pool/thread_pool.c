#include "thread_pool.h"
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

void init_thread_pool(thread_pool *tp, size_t th_num, size_t q_size)
{
  int i;
  tp->thread_num = th_num;
  tp->threads = (pthread_t *)malloc(sizeof(pthread_t) * th_num);

  tp->jobs = (thread_safe_queue *)malloc(sizeof(thread_safe_queue));
  init_queue(tp->jobs, q_size);

  for (i = 0; i < tp->th_num; ++i) {
    pthread_create(&tp->threads[i], NULL, thread_work, (void *)tp);
  }
}

void add_job_in_pool(thread_pool *tp, job_t *job)
{
  int status = enqueue(tp->jobs, (char*)job);
  if (status != 0)
    printf("queue is full\n");
}

void free_thread_pool(thread_pool *tp)
{
  int i;
  for (i = 0; i < tp->thread_num; ++i) {
    pthread_detach(tp->threads[i]);
  }
  free(tp->threads);
  free(tp->jobs->queue);
  free(tp->jobs);
}

void free_thread_pool_with_join(thread_pool *tp)
{
  int i;
  for (i = 0; i < tp->thread_num; ++i) {
    pthread_join(tp->threads[i], NULL);
  }
  free(tp->threads);
  free(tp->jobs->queue);
  free(tp->jobs);
}

void *thread_work(void *pool)
{
  job_t job;
  char ret;

  thread_pool *tp = (thread_pool *)pool;
  printf("thread work hard\n");
  while (1) {
    ret = dequeue(&tp.jobs, &job);
    job.func(job.args);
  }
}
