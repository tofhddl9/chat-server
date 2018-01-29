#include <stdlib.h>
#include <unistd.h>

#include <sys/epoll.h>

#include "io.h"

void init_io(struct io_manager *io_m, size_t thread_num,
  size_t max_event_num, size_t handler_num)
{
  io_m->epoll_fd = epoll_create(max_event_num);
 
  io_m->max_event_num = max_event_num;

  io_m->events = (struct epoll_event *)
    malloc(sizeof(struct epoll_event) * max_event_num);
  
  init_thread_pool(&io_m->tp, thread_num, sizeof(job), max_event_num / 2);

  io_m->handlers = (void (**)(void *))
    malloc(sizeof(void (*)(void *)) * handler_num);
}

void register_handler(struct io_manager *io_m, int id, void (*handler)(void *))
{
  io_m->handlers[id] = handler;
}

void register_sock(struct io_manager *io_m, int fd, int handler_id)
{
  uint64_t id_ = handler_id;

  struct epoll_event read_event;
  read_event.events = EPOLLIN;
  read_event.data.ptr = (void *)((id_ << 32) + fd);

  epoll_ctl(io_m->epoll_fd, EPOLL_CTL_ADD, fd, &read_event);
}


void delete_sock(struct io_manager *io_m, int fd)
{
  epoll_ctl(io_m->epoll_fd, EPOLL_CTL_DEL, fd, NULL);
  close(fd);
}

void do_io(struct io_manager *io_m)
{
  int i, event_num;
  uint32_t id, fd;
  job work;

  while (1) {
    event_num =
      epoll_wait(io_m->epoll_fd,io_m->events, io_m->max_event_num, -1);

    for (i = 0; i < event_num; ++i) {
      id = (uint64_t)io_m->events[i].data.ptr >> 32;
      fd = (uint64_t)io_m->events[i].data.ptr & 0x00000000FFFFFFFF;
      work.func = io_m->handlers[id];
      work.args = (void *)&fd;

      add_job_in_pool(&io_m->tp, &work);
    }
  }
}
