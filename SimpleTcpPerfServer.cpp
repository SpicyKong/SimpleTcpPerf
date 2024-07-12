#include "SimpleTcpPerfServer.h"

void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

SimpleTcpPerfServer::SimpleTcpPerfServer() 
{
    this->serv_sock = -1;
    memset(&this->serv_addr, 0, sizeof(this->serv_addr));
    this->serv_addr.sin_family=AF_INET;
    this->serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
}

SimpleTcpPerfServer::~SimpleTcpPerfServer() 
{
    close(this->serv_sock);
}

// SimpleTcpPerfServer::SimpleTcpPerfServer(char* port) 
// {
//     this->SimpleTcpPerfServer();
//     this->setPort(port);
// }

void SimpleTcpPerfServer::setPort(char* port) 
{
    this->serv_addr.sin_port=htons(atoi(port));
}

void SimpleTcpPerfServer::run() 
{
    this->serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (this->serv_sock == -1)
        error_handling("Failed to create socket.");
    bind(this->serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr));

    listen(this->serv_sock, 1);
    
    
    struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size=sizeof(clnt_addr);
    int clnt_sock=accept(this->serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
    if(clnt_sock==-1)
        error_handling("accept() error");  
    
    char message[30];
    int str_len;
    
	
    while (1) {
        str_len=read(clnt_sock, message, sizeof(message)-1);
        if(str_len==-1)
            error_handling("read() error!");
        //printf("Message from server: %s \n", message);

    }
    
}
