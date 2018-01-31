#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
  int fd, status;
  struct sockaddr_in client_addr;
  char *buf = "Hello Server?";
  char recv_buf [1024];

  fork();
  fork();
  fork();
  fork();
  fork();
  fork();
  fork();
  fork();

  fd = socket(PF_INET, SOCK_STREAM, 0);

  memset(&client_addr, 0, sizeof(client_addr));
  client_addr.sin_family = AF_INET;
  client_addr.sin_port = htons(8888);
  client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

  status = connect(fd, (struct sockaddr *)&client_addr, sizeof(client_addr));
  if (status < 0) {
    perror("conn error\n");
    exit(1);
  }
 
  //while (1) { 
    write(fd, buf, 14);
    read(fd, recv_buf, sizeof(int));
    int fd_tmp = *(int *)&recv_buf;
    printf("recv fd : %d\n", fd_tmp);
    sleep(2);
  //}
}
