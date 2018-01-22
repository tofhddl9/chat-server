#include <stdio.h>
#include <stdlib.h>
#include "thread_safe_queue.h"

static const int q_size = 10;

void print();

int main()
{
  void (*fp)();
  thread_safe_queue *q = NULL;
  q = (thread_safe_queue *)malloc(sizeof(thread_safe_queue));
  q->queue = (void **)malloc(sizeof(void *) * q_size);
  
  init_queue(&q, q_size);
  fp = print;
  
  enqueue(&q, fp);
  fp = dequeue(&q);
  fp();

  return 0;
}

void print()
{
  printf("print() is called\n");
}
