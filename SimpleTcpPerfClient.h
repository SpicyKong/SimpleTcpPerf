#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class SimpleTcpPerfClient {
private:
    int clnt_sock;
    struct sockaddr_in serv_addr;
public:
    SimpleTcpPerfClient();
    //SimpleTcpPerfClient(char* ip, char* port);
    void setIp(char* addr);
    void setPort(char* port);
    void run();
};
