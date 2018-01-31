#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "io.h"

#include <syscall.h>
#include <errno.h>

void wait_connection(void *fd);
void chat(void *args);

struct io_manager io_m;
struct sockaddr_in client_addr;

int main()
{
  int listen_fd, client_fd;
  struct sockaddr_in server_addr;

  listen_fd = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
  
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  server_addr.sin_port = htons(8888);

  bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(listen_fd, 256);

  init_io(&io_m, 5, 512, 2);

  register_handler(&io_m, 0, wait_connection);
  register_handler(&io_m, 1, chat);

  register_sock(&io_m, listen_fd, 0);
  
  do_io(&io_m);

  return 0;
}

void wait_connection(void *args)
{
  int id, fd, size, client_fd, client_addr_len;
  fd = (uint64_t)args & 0x00000000ffffffff;

  while (1) {
    client_addr_len = sizeof(client_addr);
    client_fd = accept(fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        break;
      }
      else {
        perror("accept() error");
        exit(1);
      }
    }
    else {
      printf("accept new client_fd : [%d]\n", client_fd);
      register_sock(&io_m, client_fd, 1);
    }
  }
  
}

void chat(void *args)
{
  int fd, readed;
  char buf[1024];
  fd = (uint64_t)args & 0x00000000ffffffff;
  
  while (1) {
    readed = read(fd, buf, 14);
    if (readed < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        break;
      } 
      else {
        perror("read() error");
        exit(1);
      }
    }
    else if (readed == 0) {
      close(fd);
      break;
    }
    else {
      printf("sended fd : %d\n",fd);
      write(fd, &fd, sizeof(fd));
    }
  }
  
  printf("[fd : %d]read finish\n", fd);
}
