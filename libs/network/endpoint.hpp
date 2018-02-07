#ifndef ENDPOINT_HPP__
#define ENDPOINT_HPP__

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
class Endpoint {
  public :
    enum Ip_protocol {
      IPV4,
      IPV6
    };

    Endpoint();
    Endpoint(std::string addr, unsigned short port);
    Endpoint(int ip_protocol, unsigned short port);
    ~Endpoint();

  private :
    struct sockaddr_in address_;
    int family_;
    const char *ip_;
    unsigned short port_;
};


#endif
