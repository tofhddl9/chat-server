#ifndef ACCEPTOR_HPP__
#define ACCEPTOR_HPP__

#include "socket.hpp"
#include "endpoint.hpp"

class Acceptor {
  public :
    Acceptor();
    Acceptor(Socket listen_sock, Endpoint ep, int backlog);
    ~Acceptor();

    int GetListenFD();
    //void Bind(Endpoint ep);
    //void Listen(int backlog);
    //void Accept(int listen_fd);
  private :
    int listen_fd_;
};

#endif
