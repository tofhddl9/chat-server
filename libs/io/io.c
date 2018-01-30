#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h> //for debugging

#include <sys/epoll.h>
#include <errno.h>
#include <fcntl.h>

#include "io.h"

#include <sys/syscall.h> //for debugging

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
  int flags = fcntl(fd, F_GETFL);
  flags = fcntl(fd, F_SETFL, flags | O_NONBLOCK);
  if (flags < 0) {
    perror("fcntl() error");
    exit(1);
  }

  uint64_t id_ = handler_id;

  struct epoll_event read_event;
  read_event.events = EPOLLIN | EPOLLET;
  read_event.data.ptr = (void *)((id_ << 32) + fd);

  flags = epoll_ctl(io_m->epoll_fd, EPOLL_CTL_ADD, fd, &read_event);
  if (flags < 0) {
    perror("epoll_ctl() error");
    exit(1);
  }
}

void delete_sock(struct io_manager *io_m, int fd)
{
  epoll_ctl(io_m->epoll_fd, EPOLL_CTL_DEL, fd, NULL);
  close(fd);
}

void do_io(struct io_manager *io_m)
{
  int i, event_num, int_size;
  uint32_t id, fd;
  job j;

  while (1) {
    event_num =
      epoll_wait(io_m->epoll_fd, io_m->events, io_m->max_event_num, -1);
    if (event_num < 0) {
      perror("epoll_wait() error");
      exit(1);
    }

    for (i = 0; i < event_num; ++i) {
      if ((io_m->events[i].events & EPOLLERR) ||
          (io_m->events[i].events & EPOLLHUP) ||
          (!(io_m->events[i].events & EPOLLIN))) {
        perror("epoll error");
        //fd = (uint64_t)io_m->events[i].data.ptr & 0x00000000FFFFFFFF;
        //close(fd);
        continue;
      }
      
      id = (uint64_t)io_m->events[i].data.ptr >> 32;
      fd = (uint64_t)io_m->events[i].data.ptr & 0x00000000FFFFFFFF;
      j.func = io_m->handlers[id];
      j.args = (void *)fd;
      printf("[tid:%ld][fd:%d] event is occured!\n", syscall(SYS_gettid), fd);
      add_job_in_pool(&io_m->tp, &j);
    }

  }
  
}
