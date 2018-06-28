#pragma once
#include<Windows.h>
class XscreenXor
{
	
private:
	HWINSTA hscreenDC;
	HDESK hdesk_current;
	HWINSTA hwinsta;
	HDESK hdesk;
	char *m_pdata;
	BYTE *m_pdataSave;
	int m_BmpSize;
	int m_infoSize;
	int m_scrWidth;
	int m_scrHeigth;
	int m_ncolor;

public:
	XscreenXor();  //���캯����
	~XscreenXor();  //��������
	void Set_Color(int iColor); //����ɫֵ����
	void init_GlobaVal();  //������������Ļ�߿��������λͼm_BmpSizeռ�õĿռ䣬����m_BmpSize��С�Ŀռ��m_pdata����m_pdataSave
	void Save_Screen_bits();
	void Capture_Zero_Frame();
	void Capture_First_Frame();
	void Capture_second_Frame();
	void Xor_Frame();
	void Save_Bitmap();
	void Xor_Bitmap();
	void BitmapRestore();
	bool Open_User_Desktop();
	bool Colose_User_Desktop();
	void Save_file();
	void showpic(int cyDib);
};
