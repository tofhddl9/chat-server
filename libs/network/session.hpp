#ifndef SESSION_HPP__
#define SESSION_HPP__

#include "socket.hpp"

#include <string>

class Session {
  public :
    Session();
    ~Session();
    void PostReceive();
    void PostWrite();
  
  private :
    void HandleReceive();
    void HandleWrite();
  
    Socket socket_;
    std::string write_message_;
    char receive_buf_[1024];
};

#endif
