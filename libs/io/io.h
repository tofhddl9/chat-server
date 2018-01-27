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
void register_sock(struct io_manager *io_m, int fd, int8_t fd_type, );
void delete_sock(struct io_manager *io_m, int fd);
void do_io(struct io_manager *io_m, listen_sock_handler, client_sock_handler);
#endif
