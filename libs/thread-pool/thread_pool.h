#include <pthread.h>

typedef struct jobQueue {
  void (*job)(void) *queue;
  int head;
  int tail;
  int size;
  //TODO : make thread-safety

}jobQueue;

typedef struct threadPool {
  jobQueue jobQueue;
  pthread_t *threads;
  int threadNum;
  
}threadPool;

int IsEmpty(jobQueue *jq);
int IsFull(jobQueue *jq);
void JobQueueInit(jobQueue *jq, int queueSize);
void Enqueue(jobQueue &jq, void (*job)(void));
void (*job)(void) Dequeue(jobQueue *jq);

threadPool *ThreadPoolCreate(int threadNum, int queueSize);
void ThreadPoolAdd(threadPool *tp, void *func());

//void *WaitJob(threadPool *tp);
void ThreadWork();
