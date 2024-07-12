#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class SimpleTcpPerfServer {
private:
    int serv_sock;
    struct sockaddr_in serv_addr;
public:
    SimpleTcpPerfServer();
    //SimpleTcpPerfServer(char* port);
    void setPort(char* port);
    void run();
    ~SimpleTcpPerfServer();
};
