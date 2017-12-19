
// HearthstoneBotDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "HearthstoneBot.h"
#include "HearthstoneBotDlg.h"
#include "afxdialogex.h"
#include "wininet.h"
#pragma comment(lib, "wininet.lib")
#define HIMETRIC_INCH 2540

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CHearthstoneBotDlg ��ȭ ����




CHearthstoneBotDlg::CHearthstoneBotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHearthstoneBotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHearthstoneBotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_my_browser);
}

BEGIN_MESSAGE_MAP(CHearthstoneBotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CHearthstoneBotDlg �޽��� ó����

BOOL CHearthstoneBotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	COleSafeArray post_data;
	COleVariant target_url("http://media.services.zam.com/v1/media/byName/hs/cards/enus/CS2_231.png", VT_BSTR);
	COleVariant headers((LPCTSTR)NULL, VT_BSTR);
	COleVariant target_frame_name((LPCTSTR)NULL, VT_BSTR);
	COleVariant flags((long)0, VT_I4);

	m_my_browser.Navigate2(target_url, flags, target_frame_name, post_data, headers);
	
	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CHearthstoneBotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CHearthstoneBotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.
		
		if(mp_image_object != NULL) {
			mp_image_object->Render(dc.m_hDC, m_display_rect.left, m_display_rect.top, m_display_rect.Width(), m_display_rect.Height(), 0, m_logical_height, m_logical_width, -m_logical_height, NULL);
		}
		

	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CHearthstoneBotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void imageDown() {
	HANDLE hWaitEvent = CreateEvent(NULL, TRUE, FALSE, _T("GIFW_01"));
	HINTERNET hInternet;
	hInternet = InternetOpen(_T("ŷ�����䷯����"), PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
	
	HINTERNET hConnect = ::InternetConnectA(hInternet, "http://media.services.zam.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0 ,0);
	
	HINTERNET hHttpFile = ::HttpOpenRequest(hConnect, _T("GET"), _T("/v1/media/byName/hs/cards/enus/CS2_231.png"), HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

	BOOL requestFlag = ::HttpSendRequest(hHttpFile, NULL, 0, 0, 0);

	if(requestFlag == TRUE) {
		FILE *pFile = fopen("CS2_231.png", "wb");

		char buffer[1025], errorCount = 0;
		DWORD readByte = 0, bufferSize = 1024;

		while(::InternetReadFile(hHttpFile, buffer, bufferSize, &readByte)) {
			if(readByte > 0 && pFile != NULL)
				fwrite(buffer, 1, readByte, pFile);

			if(readByte < 1024) {
				errorCount++;
				if(errorCount > 5)
					break;
				else
					::WaitForSingleObject(hWaitEvent, 50);
			}
			else
				errorCount = 0;
		}
	
	::InternetCloseHandle(hHttpFile);
	if(pFile != NULL)
		fclose(pFile);

	}
	
	::InternetCloseHandle(hConnect);
	::InternetCloseHandle(hInternet);

	CloseHandle(hWaitEvent);
}



struct TempImageData {
	int size;
	char data[1024];
};

DWORD CHearthstoneBotDlg::GetImageFromWeb(CPtrList *parmList) {
	HANDLE hWaitEvent = CreateEvent(NULL, TRUE, FALSE, "CS2_231");
	DWORD totalSize = 0;
	HINTERNET hInternet = InternetOpen("ŷ�����䷯����", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);

	HINTERNET hConnect = ::InternetConnectA(hInternet, "http://media.services.zam.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0 ,0);
	
	HINTERNET hHttpFile = ::HttpOpenRequest(hConnect, "GET", "/v1/media/byName/hs/cards/enus/CS2_231.png", HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

	BOOL requestFlag = ::HttpSendRequest(hHttpFile, NULL, 0, 0, 0);

	if(requestFlag == TRUE) {
		TempImageData *pBuffer = new TempImageData;
		char errorCount = 0;
		DWORD readByte = 0, bufferSize = 1024;

		while(::InternetReadFile(hHttpFile, pBuffer, bufferSize, &readByte)) {
			if(readByte <= 0)
				delete pBuffer;
			else {
				totalSize += readByte;
				pBuffer->size = readByte;
				parmList->AddTail(pBuffer);
			}
			pBuffer = new TempImageData;
			
			if(readByte < 1024) {
				errorCount++;
				if(errorCount > 5)
					break;
				else
					::WaitForSingleObject(hWaitEvent, 50);
			}
			else
				errorCount = 0;
		}
		delete pBuffer;

		::InternetCloseHandle(hHttpFile);
	}

	::InternetCloseHandle(hConnect);
	::InternetCloseHandle(hInternet);
	
	CloseHandle(hWaitEvent);

	return totalSize;
}

void CHearthstoneBotDlg::LoadImageToPtrList(CPtrList *parmList, DWORD parmTotalSize) {
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, parmTotalSize);
	if(NULL != hGlobal) {
		char *pData = (char *)GlobalLock(hGlobal);

		if(NULL != pData) {
			TempImageData *pBuffer = NULL;
			int currentPos = 0;
			while(!parmList->IsEmpty()) {
				pBuffer = (TempImageData *)parmList->RemoveHead();

				memcpy(pData + currentPos, pBuffer->data, pBuffer->size);
				currentPos += pBuffer->size;
			}
			GlobalUnlock(hGlobal);
		}

		LPSTREAM pStream = NULL;

		HRESULT hResult = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);
		if(SUCCEEDED(hResult) && pStream) {
			::OleLoadPicture(pStream, parmTotalSize, FALSE, IID_IPicture, (LPVOID *)&mp_image_object);
			pStream->Release();

			if(SUCCEEDED(hResult) && mp_image_object) {
				mp_image_object->get_Width(&m_logical_width);
				mp_image_object->get_Height(&m_logical_height);

				CClientDC dc(this);

				m_real_width = MulDiv(m_logical_width, dc.GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
				m_real_height = MulDiv(m_logical_height, dc.GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);

				InvalidateRect(m_display_rect);
			}
		}
		GlobalFree(hGlobal);
	}
}
