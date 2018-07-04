#include"Ping_imcp.h"
#include<iostream>

using namespace std;
void Cping::socket_init()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);  //��socket�汾����windos����ϵͳ�ϣ�ʹ��socket��Ҫ�Ȱ󶨰汾

	//����ԭʼ�׽���
	sraw = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	int time = 1000;
	//���ó�ʱʱ��
	int ret = ::setsockopt(sraw, SOL_SOCKET, TRUE ? SO_RCVTIMEO : SO_SNDTIMEO, (char*)&time, sizeof(time));
	if (ret== SOCKET_ERROR)
	{
		cout << "setsockopt_ERROR" << endl;
	}
}
//�������IP��ַת��Ϊ���ʮ������
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
	pIcmp = (ICMP_HDR*) buff;  //pIcmpָ��Ŀ�ʼ��ַָ����buff�Ŀ�ʼ��ַ
	unsigned short nSeq = 0;
	pIcmp->icmp_type = 8; //��������
	pIcmp->icmp_code = 0;
#if defined(__linux__)  //���ݲ���ϵͳ�жϱ�����һ�����
	pIcmp->icmp_id=(unsigned short)pthread_t pthread_self()
#elif defined(_WIN32)
	pIcmp->icmp_id = (unsigned short)GetCurrentProcessId();
#endif
	pIcmp->icmp_checksum = 0;
	pIcmp->icmp_sequence = 0;
//���icmp��
	memset(&buff[sizeof(ICMP_HDR)], 'E', 32);  //��32λ���ΪE
	pIcmp->icmp_timestamp = GetTickCount();//������ϵͳ���������ĺ�����
	pIcmp->icmp_sequence =nSeq++;
	pIcmp->icmp_checksum = checksum((unsigned short *)buff, sizeof(buff));
}
//����ICMP���
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
	// ������              
	if (size)
	{
		cksum += *(unsigned short*)buff;
	}
	// ��32λ��chsum��16λ�͵�16λ��ӣ�Ȼ��ȡ��           
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);    // ???               
	return (unsigned short)(~cksum);
}
void Cping::dest_set(char *ip)
{
	//����ɨ���IP��ַ
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);
	inet_pton(AF_INET, ip, &dest.sin_addr.S_un.S_addr);
}
bool Cping::run()
{
	//��ʼɨ��
	if(!ICMP_sendto())  //����ʧ�ܣ��Է�δ���
	{
		return false;
	}
	if (!ICMP_recvform())//����ʧ�ܣ��Է�δ���
	{
		return false;
	}
	return true;  //���
}
Cping::Cping()
{
	socket_init();  //����sokcet;
	pIcmp_set(); //��䱨��
}