#include"Ping_imcp.h"
#include<iostream>

using namespace std;
void Cping::socket_init()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //绑定socket版本，在windos操作系统上，使用socket都要先绑定版本

	//创建原始套节字
	sraw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int time = 1000;
	//设置超时时间
	int ret = ::setsockopt(sraw, SOL_SOCKET, TRUE ? SO_RCVTIMEO : SO_SNDTIMEO, (char*)&time, sizeof(time));
	if (ret== SOCKET_ERROR)
	{
		cout << "setsockopt_ERROR" << endl;
	}
}
//将输入的IP地址转换为点分十进制数
//void Cping::change(int a, int b, int c, int d, char IP[20])
//{
//	char IPPort[4][4] = { '\0' };
//	char temp[2] = { '.','\0' };
//	itoa(a, IPPort[0], 10);
//	itoa(b, IPPort[1], 10);
//	itoa(c, IPPort[2], 10);
//	itoa(d, IPPort[3], 10);
//	strcat(IP, IPPort[0]);
//	strcat(IP, temp);
//	strcat(IP, IPPort[1]);
//	strcat(IP, temp);
//	strcat(IP, IPPort[2]);
//	strcat(IP, temp);
//	strcat(IP, IPPort[3]);
//}
void Cping::pIcmp_set()
{
	pIcmp = (ICMP_HDR*) buff;  //pIcmp指针的开始地址指向了buff的开始地址
	unsigned short nSeq = 0;
	pIcmp->icmp_type = 8; //设置类型
	pIcmp->icmp_code = 0;
#if defined(__linux__)  //根据操作系统判断编译那一条语句
	pIcmp->icmp_id=(unsigned short)pthread_t pthread_self()
#elif defined(_WIN32)
	pIcmp->icmp_id = (unsigned short)GetCurrentProcessId();
#endif
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
//填充icmp包
	memset(&buff[sizeof(ICMP_HDR)], 'E', 32);  //将32位填充为E
	pIcmp->icmp_timestamp = GetTickCount();//返回自系统开机以来的毫秒数
	pIcmp->icmp_sequence =nSeq++;
	pIcmp->icmp_checksum = checksum((unsigned short *)buff, sizeof(buff));
}
//发送ICMP封包
bool Cping::ICMP_sendto()
{
	int ret=sendto(sraw, buff, sizeof(buff),0,(sockaddr *)&dest,sizeof(dest));
	if (ret == -1)
	{
		printf("sendto() failed:%d\n", ::WSAGetLastError());
		return false;
	}
	else
	{
		return true;
	}
}
bool Cping::ICMP_recvform()
{
	char rebuf[1024];
	int len = sizeof(from);
	int ret = recvfrom(sraw, rebuf, 1024, 0, (sockaddr *)&from,&len);
	if (ret == -1)
	{
		printf("recvfrom() failed:%d\n",WSAGetLastError());
		return false;
	}
	else
	{
		return true;
	}
}
unsigned short Cping::checksum(unsigned short *buff, int size)
{
	unsigned long cksum = 0;
	while (size>1)
	{
		cksum += *buff++;
		size -= sizeof(unsigned short);
	}
	// 是奇数              
	if (size)
	{
		cksum += *(unsigned short*)buff;
	}
	// 将32位的chsum高16位和低16位相加，然后取反           
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);    // ???               
	return (unsigned short)(~cksum);
}
void Cping::dest_set(char *ip)
{
	//设置扫描的IP地址
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	inet_pton(AF_INET, ip, &dest.sin_addr.S_un.S_addr);
}
bool Cping::run()
{
	//开始扫描
	if(!ICMP_sendto())  //发送失败，对方未存活
	{
		return false;
	}
	if (!ICMP_recvform())//接受失败，对方未存活
	{
		return false;
	}
	return true;  //存活
}
Cping::Cping()
{
	socket_init();  //设置sokcet;
	pIcmp_set(); //填充报文
}