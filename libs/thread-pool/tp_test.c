#include <stdio.h>
#include <stdlib.h>
#include "thread_pool.h"


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
  job j[230];
  struct triple_int_add_args a1[230];

  thread_pool *tp = NULL;
  tp = (thread_pool *)malloc(sizeof(thread_pool));
  init_thread_pool(tp, 5, sizeof(j[0]), 100);
  
  int ret;
  for (i = 0 ;i < 230; ++i) {
    j[i].func = triple_int_add;
    j[i].args = (void *)&a1[i];
    a1[i].a = 0;
    a1[i].b = 0;
    a1[i].c = i;
    while ((ret = add_job_in_pool(tp, &j[i])) < 0);

  }
  free_thread_pool_with_join(tp);
  return 0;
}
