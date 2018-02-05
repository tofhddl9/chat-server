#ifndef SESSION_HPP__
#define SESSION_HPP__

#include "Socket.hpp"

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
  
    const int BUF_SIZE = 1024;
    Socket socket_;
    std::string write_message_;
    char receive_buf_[BUF_SIZE];
}

#endif
