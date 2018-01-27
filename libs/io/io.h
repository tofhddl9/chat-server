#ifndef IO_H
#define IO_H

struct io_manager {
  int epoll_fd;
  int listen_fd;
  size_t max_event_num;
  struct epoll_event *events;
  struct thread_pool tp;
}

void init_io(struct io_manager *io_m, size_t thread_num, size_t max_event_num);
void register_sock();
void delete_sock();
void do_io();
#endif
