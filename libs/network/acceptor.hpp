#ifndef ACCEPTOR_HPP__
#define ACCEPTOR_HPP__

#include "Socket.hpp"
#include "Endpoint.hpp"

class Acceptor {
  public :
    Acceptor(Socket listen_sock, Endpoint ep, int backlog);
    ~Acceptor();

    void Bind(Endpoint ep);
    void Listen(int backlog);
    void Accept(Socket listen_fd);
  private :
}

#endif
