#ifndef TCP_SOCKET_HPP__
#define TCP_SOCKET_HPP__

#include <vector>
#include <list>
#include "session.hpp"
#include "acceptor.hpp"
#include "socket.hpp"
#include "endpoint.hpp"
#include "../io/io.h"

class TCP_Server {
  public :
    TCP_Server();
    TCP_Server(std::string address, unsigned short port);
    ~TCP_Server();
    void CloseSession();
 
  protected :
    virtual void AcceptHandler();
    
  private :
    void Init(int max_session_num);
    void RegisterHandler(int handler_num, int fd, void (*handler)(void *));
    bool StartAccept(int accept_handler_num);
    
    struct io_manager io_m_;
    Acceptor acceptor_;
    bool is_accepting_;
    std::list<int> session_list_;
    std::vector<Session *> session_queue_;
};

#endif
