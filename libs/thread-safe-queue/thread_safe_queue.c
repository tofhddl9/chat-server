#include <stdlib.h>

#include "thread_safe_queue.h"


thread_safe_queue *create_queue(size_t element_size, size_t q_size)
{
  thread_safe_queue *sq = NULL;
  sq->queue = (void *)malloc(element_size * q_size); 
  sq->size = q_size;
  sq->head = sq->tail = 0;

  return sq;
}

int is_empty(thread_safe_queue *sq)
{
  if (sq->head == sq->tail)
    return 1;
  return 0;
}

int is_full(thread_safe_queue *sq)
{
  if (sq->head == ((sq->tail+1) % sq->size))
    return 1;
  return 0;
}

void enqueue(thread_safe_queue *sq, job_t job)
{
  //lock
  if (is_full(sq) != 0) {
    sq->queue[(sq->tail+1)%(sq->size)] = job;
  }
  //else error
  //unlock
}

job_t dequeue(thread_safe_queue *sq)
{
  //lock
  job_t job;
  if (is_empty(sq) != 0) {
    job = sq->queue[sq->head];
    sq->head = (++(sq->head) % sq->size);
  }
  //unlock
  return job;
}
