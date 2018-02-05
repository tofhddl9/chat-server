#ifndef SOCKET_HPP__
#define SOCKET_HPP__

class Socket {
  public :
    Socket();
    Socket(int domain, int type);
    ~Socket();
    
    void Connect();
    void ReadSome();
    void WriteSome();
    void IsOpen();
    void Close();
  protected :
    int fd_;

  private :
}

#endif
