
// HearthstoneBotDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "HearthstoneBot.h"
#include "HearthstoneBotDlg.h"
#include "afxdialogex.h"
#include "wininet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CHearthstoneBotDlg 대화 상자




CHearthstoneBotDlg::CHearthstoneBotDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHearthstoneBotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CHearthstoneBotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHearthstoneBotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CHearthstoneBotDlg 메시지 처리기

BOOL CHearthstoneBotDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CHearthstoneBotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CHearthstoneBotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void imageDown() {
	HANDLE hWaitEvent = CreateEvent(NULL, TRUE, FALSE, _T("GIFW_01"));
	HINTERNET hInternet;
	hInternet = InternetOpen(_T("킹갓엠페러위습"), PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
	
	HINTERNET hConnect = ::InternetConnectA(hInternet, "http://media.services.zam.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0 ,0);
	
	HINTERNET hHttpFile = ::HttpOpenRequest(hConnect, "GET", _T("/v1/media/byName/hs/cards/enus/CS2_231.png"), HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

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
	HANDLE hWaitEvent = CreateEvent(NULL, TRUE, FALSE, _T("GIFW_01"));
	DWORD totalSize = 0;
	HINTERNET hInternet = InternetOpen(_T("킹갓엠페러위습"), PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);

	HINTERNET hConnect = ::InternetConnectA(hInternet, "http://media.services.zam.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0 ,0);
	
	HINTERNET hHttpFile = ::HttpOpenRequest(hConnect, "GET", _T("/v1/media/byName/hs/cards/enus/CS2_231.png"), HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

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