#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"

static int val = 0;

void *add_one(int *tmp)
{
  *tmp = *tmp + 1;
}

int main()
{
  int i;
  thread_pool *tp = NULL;
  tp = (thread_pool *)malloc(sizeof(thread_pool));
  init_thread_pool(tp, 10, 200);
 
  for (i = 0 ;i < 400; ++i) {
    add_job_in_pool(tp, add_one(&val));
    printf("head:%d tail:%d val:%d\n",tp->jobs->head, tp->jobs->tail, val);
  }
  printf("%d\n",val);

  return 0;
}
