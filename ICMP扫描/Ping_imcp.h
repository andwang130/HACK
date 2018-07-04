#pragma once
#if defined(__linux__)
#include <pthread.h>
#include <time.h>
//linux获取线程号需要的头
#elif defined(_WIN32)
#define _WINSOCKAPI_
#include<Windows.h>
#include<WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

//winods获取线程号需要的头
#endif
typedef unsigned long Ipaddr;

typedef struct ip_head
{
	unsigned int headlen : 4; //ip头长度
	unsigned int version : 4;  //ip版本号
	unsigned char tos;//服务类型
	unsigned short id;  //id号
	unsigned short flag;//标记
	unsigned char tll;//生存时间
	unsigned  char prot; //协议
	unsigned short checksum;           //效验和
	unsigned int sourceIP;             //源IP
	unsigned int destIP;               //目的IP
}IpHeader;
typedef struct icmp_hdr
{
	unsigned char   icmp_type;   // 消息类型            
	unsigned char   icmp_code;   // 代码              
	unsigned short icmp_checksum; // 校验和            
								  // 下面是回显头           
	unsigned short icmp_id;   // 用来惟一标识此请求的ID号，通常设置为进程ID            
	unsigned short icmp_sequence; // 序列号            
	unsigned long   icmp_timestamp; // 时间戳              
} ICMP_HDR, *PICMP_HDR;
class Cping
{ 
private:
	char buff[sizeof(ICMP_HDR) + 32];
	SOCKET sraw;
	ICMP_HDR *pIcmp;
	sockaddr_in dest;  //目标主机sockaddr_in信息
	sockaddr_in from;//f返回的sockaddr_in
	void socket_init();
	void change(int a, int b, int c, int d, char IP[20]);
	void pIcmp_set();
	bool ICMP_sendto();
	bool ICMP_recvform();
	unsigned short checksum(unsigned short *buff, int size);
public:
	Cping();
	void dest_set(char *ip);
	bool run();
};