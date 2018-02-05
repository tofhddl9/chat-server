#ifndef TCP_SOCKET_HPP__
#define TCP_SOCKET_HPP__

#include <vector>
#include "../io/io.h"

class TCP_Server {
  public :
    TCP_Server(std::string address, unsigned short port);
    ~TCP_Server();
    Accept();
    CloseSession();
  
  private :
    void Init(int max_session_num);
    void StartAccept();
    
    struct io_manager io_m_;
    Acceptor acceptor_;
    bool is_accepting_;
    std::vector<int> session_queue_;
    std::vector<Session *> session_list_;
}

#endif
