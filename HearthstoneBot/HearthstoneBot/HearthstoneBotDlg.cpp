
// HearthstoneBotDlg.cpp : 구현 파일
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
		
		dc.Rectangle(10,10,50,50);
		if(mp_image_object != NULL){
        // 그림이 선택되어 읽혀진 상태라면 화면에 출력한다.
			mp_image_object->Render(dc.m_hDC, m_display_rect.left, m_display_rect.top, m_display_rect.Width(), m_display_rect.Height(), 0, m_logical_height, m_logical_width, -m_logical_height, NULL);
		}
		
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

/*
void imageDown() {
	HANDLE hWaitEvent = CreateEvent(NULL, TRUE, FALSE, _T("GIFW_01"));
	HINTERNET hInternet;
	hInternet = InternetOpen(_T("킹갓엠페러위습"), PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);
	
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
*/


// 받을 이미지 정보를 1024 크기로 저장할 구조체입니다.
struct TempImageData {
	// 실제로 저장한 크기가 저장됩니다. ( 1024를 넘지 않습니다. )
	int size;
	// 이미지를 저장할 메모리입니다.
	char data[1024];
};

// 웹이미지를 CPtrList 에 1024 단위로 나누어서 저장하는 함수입니다.
// 수신받은 이미지의 전체 크기를 반환합니다.
DWORD CHearthstoneBotDlg::GetImageFromWeb(CPtrList *parm_list)	{
	// 웹서버에서 이미지를 받을때, 네트웍 지연이 발생하면 잠시 기다릴 목적으로 사용할 
	// 이벤트 객체를 생성합니다.
	HANDLE h_wait_event = CreateEvent(NULL, TRUE, FALSE, "GIFW_01");
	DWORD total_size = 0;


	// 인터넷에 있는 정보를 사용하기 위해서 세션을 구성한다.
	HINTERNET h_session = ::InternetOpen("Tipssoft Example", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);

	// www.tipssoft.com 사이트에 접속을 합니다.
	HINTERNET h_connect = ::InternetConnect(h_session, "www.tipssoft.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0, 0);

	// 접속된 사이트에서 특정 경로에 있는 파일을 읽을수 있도록 요청한다. 
	// 그림의 경로를 명시할때는 사이트 주소를 제외한 나머지 경로만 명시하면 됩니다.
	HINTERNET h_http_file = ::HttpOpenRequest(h_connect, "GET", "/img/logo.jpg", HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

	// 지정한 파일의 내용을 전송할것을 요청한다.
	BOOL request_flag = ::HttpSendRequest(h_http_file, NULL, 0, 0, 0);
	if(request_flag == TRUE){
		// 이미지를 1024크기로 나누어 받을 구조체를 생성합니다.
		TempImageData *p_buffer = new TempImageData;
		char error_count = 0;
		DWORD read_byte = 0, buffer_size = 1024;


		// 한번에 최대 1024 크기만큼 네트워크를 통해서 그림정보를 수신합니다.
		while(::InternetReadFile(h_http_file, p_buffer->data, buffer_size, &read_byte)){
			// 제대로 수신하지 못했다면 리스트에 추가하지 않습니다.
			if(read_byte <= 0) delete p_buffer;
			else {
				// 전체 크기에 현재 수신된 크기를 합산합니다.
				total_size += read_byte;
				// 1바이트라도 수신했다면 리스트에 추가합니다.
				p_buffer->size = read_byte;
				parm_list->AddTail(p_buffer);
			}


			// 다음 1024바이트를 수신할 구조체를 생성합니다.
			p_buffer = new TempImageData;

			if(read_byte < 1024){
				// 1024 보다 적은 경우를 읽은 경우, 렉에 의해서 못읽는 경우도 있기 때문에
				// 최대 5번까지 재시도한다. 재시도를 하는 경우 50ms의 지연시간을 부여하여
				// 전송을 기다리도록 한다.
				error_count++;
				if(error_count > 5) break;
				else ::WaitForSingleObject(h_wait_event, 50);
			} else error_count = 0;
		}


		delete p_buffer;


		// 그림을 수신하기 위해 생성한 정보를 닫는다.
		::InternetCloseHandle(h_http_file); 
	}

	// 인터넷을 사용하기 위해서 연결한 핸들과 세션 핸들을 닫는다.
	::InternetCloseHandle(h_connect);
	::InternetCloseHandle(h_session);


	// 이벤트 객체를 제거한다.
	CloseHandle(h_wait_event);

	// 전체 수신된 크기를 반환합니다.
	return total_size;
}

void CHearthstoneBotDlg::LoadImageToPtrList(CPtrList *parm_list, DWORD parm_total_size) {
	// 이미지를 한개의 스트림으로 만들기 위해서 이미지 전체크기로 메모리를 생성합니다.
	HGLOBAL h_global = GlobalAlloc(GMEM_MOVEABLE, parm_total_size);
	if(NULL != h_global){
		// 핸들 형태로 할당된 전역 메모리를 사용하기 위해서 실제 포인터를 얻습니다.
		char *p_data = (char *)GlobalLock(h_global);

		if(NULL != p_data){
			TempImageData *p_buffer = NULL;
			int current_pos = 0;

			while(!parm_list->IsEmpty()){
				// 리스트의 시작에 저장되어 있는 구조체를 얻고 해당 노드는 삭제합니다.
				p_buffer = (TempImageData *)parm_list->RemoveHead();


				// 얻어온 구조체를 스트림에 추가합니다.
				memcpy(p_data + current_pos, p_buffer->data, p_buffer->size);
				// 추가할 위치를 갱신합니다.
				current_pos += p_buffer->size;
				// 복사후, 1024로 나눈 단위 이미지는 제거합니다.
				delete p_buffer;
			}


			GlobalUnlock(h_global);
		}


		LPSTREAM p_stream = NULL;
		// 읽어들인 파일정보를 이용하여 스트림 객체를 생성합니다.
		HRESULT h_result = CreateStreamOnHGlobal(h_global, TRUE, &p_stream);
		if(SUCCEEDED(h_result) && p_stream){
			// 스트림 객체의 내용을 기준으로 그림(Picture) 객체를 생성합니다.
			// 생성된 그림 객체의 포인터는 mp_image_object에 저장됩니다.
			::OleLoadPicture(p_stream, parm_total_size, FALSE, IID_IPicture, (LPVOID *)&mp_image_object);
			// 스트림 객체를 제거합니다.
			p_stream->Release();

			if(SUCCEEDED(h_result) && mp_image_object){
				// 이미지의 논리적 절대 크기를 얻습니다.
				mp_image_object->get_Width(&m_logical_width);
				mp_image_object->get_Height(&m_logical_height);

				CClientDC dc(this);
				// 현재 DC에 맞도록 크기를 재조정합니다.
				m_real_width = MulDiv(m_logical_width, dc.GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
				m_real_height = MulDiv(m_logical_height, dc.GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);

				// 화면을 갱신하여 그림을 보여줍니다.
				InvalidateRect(m_display_rect);
			}
		}

		GlobalFree(h_global);
	}
}