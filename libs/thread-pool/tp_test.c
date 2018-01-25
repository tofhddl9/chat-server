#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"

static int val = 0;

struct triple_int_add_args {
  int a;
  int b;
  int c;
};

void triple_int_add(void *args)
{
  int sum = 0;
  struct triple_int_add_args *tiaa = (struct triple_int_add_args *)args;
  printf("%d\n",tiaa->a + tiaa->b + tiaa->c);
}

int main()
{
  int i;
  job j;
  struct triple_int_add_args a1 = {1,2,3};

  j.func = triple_int_add;
  j.args = (void *)&a1;

  thread_pool *tp = NULL;
  tp = (thread_pool *)malloc(sizeof(thread_pool));
  init_thread_pool(tp, 10, sizeof(j), 400);
  
  for (i = 0 ;i < 200; ++i) {
    a1.a=0;
    a1.b=0;
    a1.c=i;
    add_job_in_pool(tp, &j);
  }
  free_thread_pool_with_join(tp);
  return 0;
}
