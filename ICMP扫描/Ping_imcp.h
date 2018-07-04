#pragma once
#if defined(__linux__)
#include <pthread.h>
#include <time.h>
//linux��ȡ�̺߳���Ҫ��ͷ
#elif defined(_WIN32)
#define _WINSOCKAPI_
#include<Windows.h>
#include<WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

//winods��ȡ�̺߳���Ҫ��ͷ
#endif
typedef unsigned long Ipaddr;

typedef struct ip_head
{
	unsigned int headlen : 4; //ipͷ����
	unsigned int version : 4;  //ip�汾��
	unsigned char tos;//��������
	unsigned short id;  //id��
	unsigned short flag;//���
	unsigned char tll;//����ʱ��
	unsigned  char prot; //Э��
	unsigned short checksum;           //Ч���
	unsigned int sourceIP;             //ԴIP
	unsigned int destIP;               //Ŀ��IP
}IpHeader;
typedef struct icmp_hdr
{
	unsigned char   icmp_type;   // ��Ϣ����            
	unsigned char   icmp_code;   // ����              
	unsigned short icmp_checksum; // У���            
								  // �����ǻ���ͷ           
	unsigned short icmp_id;   // ����Ωһ��ʶ�������ID�ţ�ͨ������Ϊ����ID            
	unsigned short icmp_sequence; // ���к�            
	unsigned long   icmp_timestamp; // ʱ���              
} ICMP_HDR, *PICMP_HDR;
class Cping
{ 
private:
	char buff[sizeof(ICMP_HDR) + 32];
	SOCKET sraw;
	ICMP_HDR *pIcmp;
	sockaddr_in dest;  //Ŀ������sockaddr_in��Ϣ
	sockaddr_in from;//f���ص�sockaddr_in
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