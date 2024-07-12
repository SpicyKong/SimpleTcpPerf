#include "SimpleTcpPerfClient.h"
#include <linux/inet_diag.h>
#include <netinet/tcp.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <linux/inet_diag.h>
#include <linux/rtnetlink.h>


void error_handling(const char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}


SimpleTcpPerfClient::SimpleTcpPerfClient() 
{
    this->clnt_sock = -1;
    memset(&this->serv_addr, 0, sizeof(this->serv_addr));
    this->serv_addr.sin_family=AF_INET;
}

// SimpleTcpPerfClient::SimpleTcpPerfClient(char* ip, char* port) 
// {
//     this->SimpleTcpPerfClient();
//     this->setPort(port);
//     this->setIp(ip);
// }

void SimpleTcpPerfClient::setIp(char* ip) 
{
    this->serv_addr.sin_addr.s_addr=inet_addr(ip);
}

void SimpleTcpPerfClient::setPort(char* port) 
{
    this->serv_addr.sin_port=htons(atoi(port));
}

void SimpleTcpPerfClient::run() 
{
    this->clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (this->clnt_sock == -1)
        error_handling("Failed to create socket.");
    if(connect(this->clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");
        
    char message[1500];
    //write(this->clnt_sock, message, sizeof(message));




    long long int bw;
    
    union tcp_cc_info info;
    for (int i=10000; i>=0; i--) {
        write(this->clnt_sock, message, sizeof(message));
    }
    socklen_t len = sizeof(info);

    if (getsockopt(this->clnt_sock, SOL_TCP, TCP_CC_INFO, &info, &len) < 0) {
      perror("getsockopt(TCP_CC_INFO)");
      exit(EXIT_FAILURE);
    }

    if (len >= sizeof(info.bbr)) {
        // printf("min_rtt: %u\n", info.bbr.bbr_min_rtt);
        // printf("bbr_bw_lo: %d\n", info.bbr.bbr_bw_lo);
	    // printf("bbr_bw_hi: %d\n", info.bbr.bbr_bw_hi);
	    // printf("bbr_min_rtt: %d\n", info.bbr.bbr_min_rtt);
	    // printf("bbr_pacing_gain: %d\n", info.bbr.bbr_pacing_gain);
	    // printf("bbr_cwnd_gain: %d\n", info.bbr.bbr_cwnd_gain);
	    // printf("bbr_bw_hi_lsb: %d\n", info.bbr.bbr_bw_hi_lsb);
	    // printf("bbr_bw_hi_msb: %d\n", info.bbr.bbr_bw_hi_msb);
	    // printf("bbr_bw_lo_lsb: %d\n", info.bbr.bbr_bw_lo_lsb);
	    // printf("bbr_bw_lo_msb: %d\n", info.bbr.bbr_bw_lo_msb);
	    printf("bbr_mode: %d\n", info.bbr.bbr_mode);
	    // printf("bbr_phase: %d\n", info.bbr.bbr_phase);
	    // printf("bbr_version: %d\n", info.bbr.bbr_version);
	    // printf("bbr_inflight_lo: %d\n", info.bbr.bbr_inflight_lo);
	    // printf("bbr_inflight_hi: %d\n", info.bbr.bbr_inflight_hi);
	    // printf("bbr_extra_acked: %d\n", info.bbr.bbr_extra_acked);
    }


    

    close(this->clnt_sock);
}

/*
	__u32	bbr_bw_lo;		    lower 32 bits of bw
	__u32	bbr_bw_hi;		    upper 32 bits of bw
	__u32	bbr_min_rtt;		min-filtered RTT in uSec
	__u32	bbr_pacing_gain;	pacing gain shifted left 8 bits
	__u32	bbr_cwnd_gain;		cwnd gain shifted left 8 bits
	__u32	bbr_bw_hi_lsb;		lower 32 bits of bw_hi
	__u32	bbr_bw_hi_msb;		upper 32 bits of bw_hi
	__u32	bbr_bw_lo_lsb;		lower 32 bits of bw_lo
	__u32	bbr_bw_lo_msb;		upper 32 bits of bw_lo
	__u8	bbr_mode;		    current bbr_mode in state machine
	__u8	bbr_phase;		    current state machine phase
	__u8	unused1;		    alignment padding; not used yet
	__u8	bbr_version;		BBR algorithm version
	__u32	bbr_inflight_lo;	lower short-term data volume bound
	__u32	bbr_inflight_hi;	higher long-term data volume bound
	__u32	bbr_extra_acked;	max excess packets ACKed in epoch

*/














