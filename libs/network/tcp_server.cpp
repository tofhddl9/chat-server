#include "tcp_server.hpp"
#include <sys/types.h>
#include <sys/socket.h>

TCP_Server::TCP_Server(std::string address, unsigned short port)
{
  Socket sock = Socket(AF_INET, SOCK_STREAM);
  Endpoint ep = Endpoint(address, port); 
  acceptor_ = Acceptor(sock, ep, 256);

  StartAccept(acceptor_.GetListenFD());
}

TCP_Server::~TCP_Server()
{
}

void TCP_Server::Init(int max_session_num)
{
  for (int i = 0; i < max_session_num; ++i) {
    Session *session = new Session();
    session_queue_.push_back(session);
    session_list_.push_back(i);
  } 
}

void TCP_Server::RegisterHandler(int handler_num, int fd, void (*handler)(void*))
{
  register_handler(&io_m_, fd, handler);
}

bool TCP_Server::StartAccept(int accept_handler_num)
{
  if (session_queue_.empty()) {
    is_accepting_ = false;
    return false; 
  }
 
  is_accepting_ = true;
  int session_id = session_list_.front();
  session_list_.pop_front();
  
  register_sock(&io_m_, acceptor_.GetListenFD(), accept_handler_num);
  
  return true;
}
