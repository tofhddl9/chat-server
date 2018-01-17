#include "thread_pool.h"

#include <stdlib.h>

void jobQueueInit(jobQueue *jq, int size)
{
  jq->size = size;
  jq->head = jq->tail = 0;
  jq = (jobQueue *)malloc(sizeof(jobQueue)*size); 
}

int IsEmpty(jobQueue *jp)
{

}

int IsFull(jobQueue *jp)
{

}

void Enqueue(jobQueue *jq, void (*job)(void))
{
  //lock
  if (IsFull(jq) != 0) {
    jq->queue[(jq->tail+1)%(jq->size)];
  }
  //else error
  //unlock
}

void (*job)(void) Dequeue(jobQueue *jq)
{
  //lock
  void (*job)(void) = NULL;
  if (IsEmpty(jq) != 0) {
    job = jq->queue[jq->head];
    head = ++head % jq->size;
  }
  return job;
}

threadPool *ThreadPoolCreate(int threadNum, int queueSize)
{
  int i;

  threadPool *tp;
  tp = (threadPool *)malloc(sizeof(threadPool));
  JobQueueInit(&(tp->jobQueue), queueSize);
  
  tp->threadNum = threadNum;
  tp->threads = (pthread_t *)malloc(sizeof(pthread_t) * threadNum);
  for (i = 0; i < threadNum; ++i) {
    pthread_create(&(tp->threads[i]), NULL, ThreadWork, (void *)tp);
  }

  return tp;
}

void ThreadPoolAddJob(threadPool *tp, void (*job)())
{
  //lock
  if (!IsFull(tp->jobQueue)) {
    Enqueue(tp->jobQueue, job);
  }
  //unlock
}

void ThreadWork(void *pool)
{
  threadPool *tp = (threadPool *)pool;
  void (*fp)();
  while (1) {
    //lock
    if (!IsEmpty(tp->jobQueue)) { //WaitJob
      fp = Dequeue(tp->jobQueue);
      fp();
    }
    //unlock
  }
}
