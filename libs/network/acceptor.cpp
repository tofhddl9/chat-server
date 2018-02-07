#include "acceptor.hpp"

Acceptor::Acceptor(Socket listen_sock, Endpoint ep, int backlog)
{
  listen_fd_ = listen_sock.GetFD();

  int flag;
  flag = bind(listen_sock.fd_,
    (struct sockaddr *)&ep.address, sizeof(ep.address));
  if (flag < 0) {
    perror("bind() error");
    exit(1);
  }

  flag = listen(listen_sock.fd_, backlog);
  if (flag < 0) {
    perror("listen() error");
    exit(1);
  }
}

int Acceptor::GetListenFD()
{
  return listen_fd_;
}
