#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "io.h"

int main()
{
  int listen_fd, client_fd;
  struct sockaddr_in server_addr, client_addr;
  struct io_manager io_m;

  listen_fd = socket(PF_INET, SOCK_STREAM, 0);
  setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
  
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  server_addr.sin_port = htons(7777);

  bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(listen_fd, 128);

  init_io(&io_m, 5, 128, 2);

  return 0;
}
