#include "io.h"
#include <sys/epoll.h>
#include "thread-pool/thread-pool.h"

void init_io(struct io_manager *io_m, size_t thread_num, size_t max_event_num)
{
  struct epoll_event event = {EPOLLIN, listen_fd};

  io_m->epoll_fd = epoll_create(1);
  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &event); 
 
  io_m->max_event_num = max_event_num;

  io_m->events = (struct epoll_event *)
    malloc(sizeof(epoll_event) * max_event_num);
  
  init_thread_pool(&io.m->tp, thread_num, element_size, max_event_num / 2);
  
}

void register_sock(struct io_manager *io_m, int fd, uint8_t is_listen_fd)
{
  struct epoll_event read_event = {EPOLLIN, listen_fd};
  
  if (is_listen_fd)
    io_m->listen_fd = fd;

  epoll_ctl(io_m->epoll_fd, EPOLL_CTL_ADD, fd, &read_event);
}

void delete_sock(struct io_manager *io_m, int fd)
{
  epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, NULL);
  close(fd);
}

void do_io(struct io_manager *io_m, listen_sock_handler, client_sock_handler)
{
  int i, event_num;

  while (1) {
    event_num = epoll_wait(io_m->epoll_fd,
        io_m->events, io_m->max_event_num, -1);

    for (i = 0; i < event_num; ++i) {
      if (events[i].data.fd == listen_fd) {
        add_job_in_pool(io_m->tp, listen_sock_handler);
      }
      else if (events.data.fd == client_fd) {
        add_job_in_pool(io_m->tp, client_sock_handler);
      }
    }
    // problem : type of 2nd param of 'add_job_in_pool' is struct job..{func, args}
  }
}
