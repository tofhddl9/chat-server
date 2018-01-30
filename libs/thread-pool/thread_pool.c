#include "thread_pool.h"
#include <stdlib.h>
#include <stdio.h>

#include <pthread.h>

#include <syscall.h>

void init_thread_pool(thread_pool *tp, size_t th_num, size_t e_size, size_t q_size)
{
  int i;
  tp->thread_num = th_num;
  tp->threads = (pthread_t *)malloc(sizeof(pthread_t) * th_num);

  init_queue(&tp->jobs, e_size, q_size);

  for (i = 0; i < tp->thread_num; ++i) {
    pthread_create(&tp->threads[i], NULL, thread_work, (void *)tp);
  }
}

int8_t add_job_in_pool(thread_pool *tp, job *work)
{
  int8_t status = enqueue(&tp->jobs,(char *)work);
  if (status != 0)
    return -1;
  return 0;
}

void free_thread_pool(thread_pool *tp)
{
  int i;
  for (i = 0; i < tp->thread_num; ++i) {
    pthread_detach(tp->threads[i]);
  }
  free(tp->threads);
  free(tp->jobs.queue);
  free(&tp->jobs);
}

void free_thread_pool_with_join(thread_pool *tp)
{
  int i;
  for (i = 0; i < tp->thread_num; ++i) {
    pthread_join(tp->threads[i], NULL);
  }
  free(tp->threads);
  free(tp->jobs.queue);
  free(&tp->jobs);
}

void *thread_work(void *pool)
{
  job work;
  char ret;

  thread_pool *tp = (thread_pool *)pool;
  printf("[%lu] thread work hard\n",syscall(SYS_gettid));

  while (1) {
    ret = dequeue(&tp->jobs, (char *)&work);
    if (ret == 0)
      work.func(work.args);
      
  }
}
