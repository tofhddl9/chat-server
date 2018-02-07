#ifndef SOCKET_HPP__
#define SOCKET_HPP__

class Socket {
  public :
    Socket();
    Socket(int domain, int type);
    ~Socket();
    
    int GetFD();
    void Connect();
    void ReadSome();
    void WriteSome();
    void IsOpen();
    void Close();

  private :
    int fd_;
};

#endif
