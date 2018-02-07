#include "endpoint.hpp"

// TODO : support ipv6
Endpoint::Endpoint(const char *addr, unsigned short port)
{
  address_.sin_family = AF_INET;
  address_.sin_addr.s_addr = inet_addr(addr);
  address_.sin_port = htons(port);

  ip_ = addr;
  port_ = port;

}

Endpoint::Endpoint(IP_protocol ip_protocol, unsigned short port)
{
  if (ip_protocol == IPV4) {
    address_.sin_family = AF_INET;
    address_.sin_addr.s_addr = inet_addr(INADDR_ANY);
    address_.sin_port = port;
  }
  ip_ = "0.0.0.0";
  port_ = port;
}

Endpoint::~Endpoint()
{
  
}
