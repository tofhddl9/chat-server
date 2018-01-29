#ifndef IO_H
#define IO_H

#include "thread-pool/thread-pool.h"

struct io_manager {
  int epoll_fd;
  size_t max_event_num;
  struct epoll_event *events;
  struct thread_pool tp;
  void (**handlers)(int);
}

void init_io(struct io_manager *io_m, size_t thread_num,
  size_t max_event_num, size_t handler_num);
void register_handler(struct io_manager *io_m, int id, void (*handler)(int));
void register_sock(struct io_manager *io_m, int fd, int handler_id);
void delete_sock(struct io_manager *io_m, int fd);
void do_io(struct io_manager *io_m);
#endif
