#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include<iostream>
#include<Windows.h>
#include<string.h>

using namespace std;
class MyCmdshell
{
public:
	string cmd_shell(string cmd_code)
	{
		/*
		ͨ��ʹ��winodws�Ĺܵ�Pipe��ʵ��ִ��CMD����ܵ�ʵ����һһ�ι����ڴ�
		�������̼�ͨ��
		*/
		STARTUPINFO si;  //STARTUPINFO����ָ���½��̵����������Ե�һ���ṹ

		PROCESS_INFORMATION pi;//�ýṹ�����й��½��̼������̵߳���Ϣ��

		HANDLE hread = NULL, hwrite = NULL; //���
		string req = "";
		char Cmdline[300] = { 0 };//�����л���
		char senbuf[2048] = { 0 };//����cmd����Ļ�������
		SECURITY_ATTRIBUTES sa; //��ȫ������
		DWORD bytesread = 0;
		int ret = 0;
		sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		sa.lpSecurityDescriptor = NULL;
		sa.bInheritHandle = TRUE;
		
		//���������ܵ�
		if (!CreatePipe(&hread, &hwrite, &sa,0))
		{
			goto clean;
		}

		si.cb = sizeof(STARTUPINFO);
		GetStartupInfo(&si);

		si.hStdError = hwrite;
		si.hStdOutput = hwrite;
		si.wShowWindow = SW_HIDE;
		si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;

		GetSystemDirectory(Cmdline, sizeof(Cmdline));  //���ϵͳCMD��Ŀ¼

		strcat_s(Cmdline, "\\cmd.exe /c ");   //strcat�����ַ���ƴ�ӣ���Ŀ¼����ƴ��
		strcat_s(Cmdline, cmd_code.c_str());  //ƴ����CMD����

		//ʹ��ƴ�Ӻ�Ŀ¼��cmd.exe��cmd�����һ��CMD����,�����˹ܵ�������ʹ�ùܵ������CMDִ�еķ�����Ϣ
		if (!CreateProcess(NULL, Cmdline, NULL, NULL,true, NULL, NULL, NULL, &si, &pi))
		{
			goto clean;
		}
		CloseHandle(hwrite);  //�رգ�ReadFile�Ų�����
		while (true)
		{
			if (ReadFile(hread, senbuf, sizeof(senbuf), &bytesread, NULL)==0)
			{
				break;
			}//���ص����ݴ�С0��������
			
			req += senbuf;
		
			memset(senbuf, 0, sizeof(senbuf));//��ջ�����
			Sleep(100);
		}
		return req;
	clean:
		if (hread!=NULL)
		{
			CloseHandle(hread);
		}
		if (hwrite != NULL)
		{
			CloseHandle(hwrite);
		}
		return "false";
	}
};