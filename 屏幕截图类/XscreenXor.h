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
	XscreenXor();  //构造函数，
	~XscreenXor();  //析构函数
	void Set_Color(int iColor); //设置色值函数
	void init_GlobaVal();  //这个函数获得屏幕高宽，来计算出位图m_BmpSize占用的空间，申请m_BmpSize大小的空间给m_pdata，和m_pdataSave
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
