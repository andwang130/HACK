#include"XscreenXor.h"
#include<iostream>
#include<fstream>
#include<opencv/cv.hpp>
#include<opencv/highgui.h>

using namespace std;
using namespace cv;
XscreenXor::XscreenXor()
{
	m_pdata = NULL;
	m_pdataSave = NULL;
	m_BmpSize = 0;  //m_BmpSizeλͼ��ռ�ռ��С
	m_infoSize = 0;  //λͼ��С
	m_scrWidth = 0;  //��Ļ���
	m_scrHeigth = 0; //��Ļ�߶�
	m_ncolor =8;
	if (Open_User_Desktop())
	{
		cout << "yes" << endl;
	}
}
XscreenXor::~XscreenXor()
{
	if (m_pdata != NULL)
	{
		delete[] m_pdata;
	}
	if (m_pdataSave != NULL)
	{
		delete[] m_pdataSave;
	}
	Colose_User_Desktop();
}
void XscreenXor::init_GlobaVal()
{
	//�����Ļ�Ŀ�͸�
	m_scrWidth = GetSystemMetrics(SM_CXSCREEN);
	m_scrHeigth = GetSystemMetrics(SM_CYSCREEN);

	int biSize = sizeof(BITMAPCOREHEADER);

	//����ɫֵ������λͼ�Ĵ�С
	if (m_ncolor >8)
	{
		m_infoSize = biSize;

	}
	else
	{
		m_infoSize = biSize + (1 << m_ncolor) * sizeof(RGBQUAD);
	}
	m_BmpSize = m_infoSize+((m_scrWidth*m_ncolor + 31) / 32 * 4)*m_scrHeigth;
	//m_BmpSize += sizeof(BITMAPFILEHEADER);

	//����λͼ�洢�ռ�
	if (m_pdata != NULL)
	{  
		delete[] m_pdata;
	}
	m_pdata = new char[m_BmpSize];
	if (m_pdataSave != NULL)
	{
		delete[] m_pdataSave;
	}
	m_pdataSave = new BYTE[m_BmpSize];

}
void XscreenXor::Set_Color(int icolor)
{
	m_ncolor = icolor;
}
bool XscreenXor::Open_User_Desktop()
{

	//�õ���ǰ���̵Ĵ���վ���,
	//����ɹ����أ�����ֵ��һ������վ�Ĵ���
	//���ʧ�ܣ�����ֵ��NULL
	hscreenDC = GetProcessWindowStation();
	if (hscreenDC == NULL)
	{
		return false;
	}
	//GetCurrentThreadId() ��ȡ��ǰ�̵߳�Ψһ��ʶ��
	//GetThreadDesktopָ���̵߳Ĵ��ھ��

	hdesk_current = GetThreadDesktop(GetCurrentThreadId());

	if (hdesk_current == NULL)
	{
		return false;
	}

	//OpenWindowStationA��ָ���Ĵ���վ
	//����ɹ�������ֵΪָ���Ĵ���վ���
	//���ʧ�ܣ�����ֵΪNuLL
	hwinsta = OpenWindowStation("winsta0", false, WINSTA_ACCESSCLIPBOARD |
		WINSTA_ACCESSCLIPBOARD |
		WINSTA_CREATEDESKTOP |
		WINSTA_ENUMDESKTOPS |
		WINSTA_ENUMERATE |
		WINSTA_EXITWINDOWS |
		WINSTA_READATTRIBUTES |
		WINSTA_READSCREEN |
		WINSTA_WRITEATTRIBUTES);
	if (hwinsta == NULL)
	{
		return false;
	}

	//SetProcessWindowStation��������ָ���Ĵ��ڹ���վ��������ý��̡�
	//��ʹ�øù��̿��Է��ʴ��ڹ���վ�еĶ����������棬�������ȫ��ԭ��
	//�����ڹ���վ�ϵ����к���������ʹ������hWinSta�ķ���Ȩ��
	//����ɹ����ط�0
	//���ʧ�ܷ���0
	if (!SetProcessWindowStation(hwinsta))
	{
		return false;
	}

	//OpenDesktop������ָ�����������
	//��������ɹ�����ָ���Ĵ��ھ��
	//���ʧ�ܷ���NULL
	 hdesk	=OpenDesktop("default", 0, false, DESKTOP_CREATEMENU |
			DESKTOP_CREATEWINDOW |
			DESKTOP_ENUMERATE |
			DESKTOP_HOOKCONTROL | 
			DESKTOP_JOURNALPLAYBACK | 
			DESKTOP_JOURNALRECORD |
			DESKTOP_READOBJECTS |
			DESKTOP_SWITCHDESKTOP| 
			DESKTOP_WRITEOBJECTS
		);
	 if (hdesk == NULL)
	 {
		 return false;
	 }
	 //SetThreadDesktop��ָ�����������������̡߳������ϵ����к���������ʹ����������ķ���Ȩ�ޡ�
	 //��������ɹ�������ֵΪ���㡣
	 //�������ʧ�ܣ�����ֵΪ�㡣
	 SetThreadDesktop(hdesk);
	 return true;
}
bool XscreenXor::Colose_User_Desktop()
{
	if (!SetProcessWindowStation(hwinsta))
	{
		return false;
	}
	if (!SetThreadDesktop(hdesk_current))
	{
		return false;
	}
	if (!CloseWindowStation(hwinsta))
	{
		return false;
	}
	if (!CloseDesktop(hdesk))
	{
		return false;
	}
	return true;
}
void XscreenXor::Save_Screen_bits()
{
	HDC hmenDC, hscreenDC;
	HBITMAP hbitmap;   
	PBITMAPINFO  pbitmapinfo;    //λͼ��Ϣ
	BITMAPINFOHEADER bi;//λͼͷ��Ϣ
	

	//��ȡ����HDC
	//hscreenDC = CreateDC("DISPLAY", NULL, NULL, NULL);
	hscreenDC = CreateDC("DISPLAY",NULL,NULL,NULL);
	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸��
	hmenDC = CreateCompatibleDC(hscreenDC);

	//����һ������Ļ�豸�������ݵ�λͼ
	hbitmap = CreateCompatibleBitmap(hscreenDC, m_scrWidth, m_scrHeigth);

	//����λͼѡ���ڴ��豸��������
	SelectObject(hmenDC, hbitmap);

	//����Ļ�豸�������Ƶ��ڴ��豸��������
	BitBlt(hmenDC, 0, 0, m_scrWidth, m_scrHeigth, hscreenDC, 0, 0, SRCCOPY);

	//tagBITMAPINFO bif;
	//bif.bmiHeader.biSize = sizeof(bif.bmiHeader);
	//bif.bmiHeader.biWidth = m_scrWidth;
	//bif.bmiHeader.biHeight = m_scrHeigth;
	//bif.bmiHeader.biPlanes = 1;
	//bif.bmiHeader.biBitCount = m_ncolor;
	//bif.bmiHeader.biCompression = 0;
	//bif.bmiHeader.biSizeImage = 0;
	////����λͼ��ͷ��Ϣ
	
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = m_scrWidth;
	bi.biHeight = m_scrHeigth;
	bi.biPlanes = 1;
	bi.biBitCount = m_ncolor;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	int colorTableSize = sizeof(RGBQUAD) * 256;
	int headerSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTableSize;
	int lineSize = (m_scrWidth*m_ncolor / 8 + 3) / 4 * 4;//the size of each line in bmp file.  
	int dataSize = lineSize * m_scrHeigth;//the size of the image data of bmp file.  
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = 'B' + ('M' << 8);
	bfh.bfSize = m_scrWidth * m_scrHeigth + 54;
	bfh.bfOffBits = 54;
	pbitmapinfo = PBITMAPINFO(m_pdata);
	//��λͼͷ��Ϣ�����Ƶ�m_pdata����
	//BYTE *NEWdata=new BYTE[sizeof(BITMAPFILEHEADER)];

	
	char *  lpbitmap = new char[m_BmpSize+sizeof(bfh)];
	//ZeroMemory(lpbitmap, m_BmpSize + sizeof(bfh));
	
	memcpy(m_pdata, (void *)&bi, sizeof(bi));
	int cyDib= GetDIBits(hmenDC, hbitmap, 0, (UINT)m_scrHeigth, m_pdata +m_infoSize, pbitmapinfo, DIB_RGB_COLORS);
	cout << cyDib << endl;
	//���
	DeleteDC(hmenDC);
	DeleteDC(hscreenDC);
	DeleteObject(hbitmap);
	memcpy(lpbitmap, (void *)&bfh, sizeof(bfh));
	memcpy(lpbitmap + sizeof(bfh), m_pdata, m_BmpSize);
	cout << strlen(lpbitmap) << endl;
	ofstream file;
	const char* filename = "dfffsd.bmp";
	file.open(filename, ios_base::binary);
	file.write(lpbitmap, sizeof(bfh) + m_BmpSize);
	file.close();
	//Save_file();
	
	delete lpbitmap;
	/*Mat img = imread(filename,-1);
	if (!img.data)
	{
		cout << img.data << endl;
	}
	else
	{
		imshow("ss", img);
		waitKey(10);
	}
	*/
}
//ԭʼ֡
void XscreenXor::Capture_Zero_Frame()
{
	Save_Screen_bits();  //�Ȼ��λͼ��Ϣ
	Save_Bitmap();//����Save_Bitmap�����ѵ�ǰλͼ��Ϣ���浽m_pdataSave��һ֡
}
//��һ֡
void XscreenXor::Capture_First_Frame()
{
	Save_Screen_bits();  //���λͼ��Ϣ
	Xor_Bitmap();  //��ǰ֡����һ֡���ÿһλ�Աȣ���һ�����滻
}
void XscreenXor::Capture_second_Frame()
{
	BitmapRestore();  //�ѵ�ǰ֡���浽��һ֡��Ҳʹ�������
	Save_Screen_bits();
	Xor_Bitmap();
}
void XscreenXor::Xor_Frame()
{
	Xor_Bitmap();
}

//������ʾ��λͼ���ݣ�ֻ�е�һ֡��ʹ�øú���
void XscreenXor::Save_Bitmap()
{
	for (int i = 0; i < m_BmpSize; i++)
	{
		m_pdataSave[i] = m_pdata[i];
	}
}
//��ǰ֡����һ֡���
void XscreenXor::Xor_Bitmap()
{
	for (int i = 0; i < m_BmpSize; i++)
	{
		m_pdata[i] ^= m_pdataSave[i];
	}
}
//���浱ǰ���ݵ���һ֡
void XscreenXor::BitmapRestore()
{
	for (int i = 0; i < m_BmpSize; i++)
	{
		m_pdataSave[i] ^= m_pdata[i];
	}
}
void XscreenXor::Save_file()
{
	ofstream file;
	const char* filename = "dsdsd.bmp";
	file.open(filename, ios::out);
	file.write((char *)m_pdata,m_BmpSize);
	file.close();
}
//void  XscreenXor::showpic(int cyDib)
//{
//	HDC hdc;
//	PAINTSTRUCT ps;
//	HINSTANCE hInstance = GetModuleHandle(NULL);
//	HWND hwnd = CreateWindowEx(NULL, "MyClass", "Title",
//		WS_OVERLAPPEDWINDOW | WS_VISIBLE, 500, 500,
//		500, 500, NULL, NULL, hInstance, NULL);
//	hdc = BeginPaint(hwnd, &ps);
//	ShowWindow(hwnd, SW_HIDE);
//	SetDIBitsToDevice(hdc,
//		0,         //�ͻ�����ʼ��ʾλͼ��x���꣬����Ĭ��ӳ�䷽	   //ʽΪWM_TEXT�������Ͻ�Ϊԭ��
//		0,         //�ͻ�����ʼ��ʾλͼ��y����
//		m_scrWidth,     // Ҫ��ʾ��λͼ�Ŀ��(cxDib��λͼ�Ŀ��
//		m_scrHeigth,     //Ҫ��ʾ��λͼ�ĸ߶�(cyDib��λͼ�ĸ߶�
//		0,         // λͼ��ԭ��λ��λͼ���½�
//		0,         //  
//		0,         //��ʼɨ���ߵ�λ��             
//		cyDib,     //ɨ���ߵ���Ŀ
//		m_pdata,
//		pbitmapinfo,
//		DIB_RGB_COLORS);
//}


void screen_get()
{
	HDC hmenDC, hscreenDC;
	HBITMAP hbitmap;
	PBITMAPINFO  pbitmapinfo;    //λͼ��Ϣ
	BITMAPINFOHEADER bi;//λͼͷ��Ϣ
	int m_scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int  m_scrHeigth = GetSystemMetrics(SM_CYSCREEN);
	cout << "x" << m_scrWidth << endl;
	cout << "y" << m_scrHeigth << endl;
	hscreenDC = GetDC(NULL);

	hmenDC = CreateCompatibleDC(hscreenDC);

	//����һ������Ļ�豸�������ݵ�λͼ
	hbitmap = CreateCompatibleBitmap(hscreenDC, m_scrWidth, m_scrHeigth);

	//����λͼѡ���ڴ��豸��������
	SelectObject(hmenDC, hbitmap);

	//����Ļ�豸�������Ƶ��ڴ��豸��������
	cout << "BitBlt" << BitBlt(hmenDC, 0, 0, m_scrWidth, m_scrHeigth, hscreenDC, 0, 0, CAPTUREBLT) << endl;;
	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = m_scrWidth;
	bi.biHeight = m_scrHeigth;
	bi.biPlanes = 1;
	bi.biBitCount = 16;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;
	DWORD size = ((m_scrWidth * 16 + 31) / 32) * 4 * m_scrHeigth;
	DWORD dwsizefDIB = size + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	BITMAPFILEHEADER bfh;
	bfh.bfReserved1 = bfh.bfReserved2 = 0;
	bfh.bfType = 0x424D;
	bfh.bfSize = dwsizefDIB;
	bfh.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD) sizeof(BITMAPINFOHEADER);
	char *  lpbitmap = new char[size];
	ZeroMemory(lpbitmap, size);
	pbitmapinfo = PBITMAPINFO(lpbitmap);
	int cyDib = GetDIBits(hmenDC, hbitmap, 0, m_scrHeigth, lpbitmap, (BITMAPINFO*)&bi, DIB_RGB_COLORS);
	cout << GetLastError() << endl;
	cout << cyDib << endl;
	ofstream file;
	const char* filename = "dfffsd.bmp";
	file.open(filename, ios_base::binary);
	char *bits = new char[size + sizeof(bfh) + sizeof(bi)];
	memcpy(bits, (void*)&bfh, sizeof(bfh));
	memcpy(bits + sizeof(bfh), (void*)&bi, sizeof(bi));
	memcpy(bits + sizeof(bfh) + sizeof(bi), lpbitmap, size);
	file.write(bits, size + sizeof(bfh) + sizeof(bi));
	file.close();

}
void screen(char* fileName)
{
	HWND window = GetDesktopWindow();
	HDC _dc = GetWindowDC(window);
	HDC dc = CreateCompatibleDC(0);
	RECT re;
	GetWindowRect(window, &re);
	int w = re.right,
		h = re.bottom;
	void* buf = new char[w*h * 4];

	HBITMAP bm = CreateCompatibleBitmap(_dc, w, h);
	SelectObject(dc, bm);

	StretchBlt(dc, 0, 0, w, h, _dc, 0, 0, w, h, SRCCOPY);

	void* f = CreateFile(fileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0);

	GetObject(bm, 84, buf);

	tagBITMAPINFO bi;
	bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
	bi.bmiHeader.biWidth = w;
	bi.bmiHeader.biHeight = h;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = 0;
	bi.bmiHeader.biSizeImage = 0;

	CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &buf, 0, 0);
	GetDIBits(dc, bm, 0, h, buf, &bi, DIB_RGB_COLORS);

	BITMAPFILEHEADER bif;
	bif.bfType = MAKEWORD('B', 'M');
	bif.bfSize = w * h * 4 + 54;
	bif.bfOffBits = 54;

	BITMAPINFOHEADER bii;
	bii.biSize = 40;
	bii.biWidth = w;
	bii.biHeight = h;
	bii.biPlanes = 1;
	bii.biBitCount = 32;
	bii.biCompression = 0;
	bii.biSizeImage = w * h * 4;

	DWORD r;
	int size = sizeof(bif) + sizeof(bii) + (w*h * 4);
	char * bits = new char[size];
	ZeroMemory(bits, size);
	memcpy(bits, (void *)&bif, sizeof(bif));
	memcpy(bits + sizeof(bif), (void *)&bii, sizeof(bii));
	memcpy(bits + sizeof(bif) + sizeof(bii), buf, w*h * 4);
	ofstream file;
	const char* filename = "dfffsd.bmp";
	file.open(filename, ios_base::binary);
	file.write(bits, size);
	file.close();

	cout << strlen(bits) << endl;
	CloseHandle(f);
	DeleteDC(_dc);
	DeleteDC(dc);
}