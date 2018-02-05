#ifndef ENDPOINT_HPP__
#define ENDPOINT_HPP__

#include <string>

class Endpoint {
  public :
    enum Ip_protocol {
      IPV4,
      IPV6
    };
    EndPoint();
    EndPoint(std::string addr, unsigned short port);
    EndPoint(IP_protocol ip_protocol, unsigned short port);
    ~EndPoint();

  private :
    std::string address_;
    unsigned short port_;
}

#endif
