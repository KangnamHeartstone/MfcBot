
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
		
		dc.Rectangle(10,10,50,50);
		if(mp_image_object != NULL){
        // �׸��� ���õǾ� ������ ���¶�� ȭ�鿡 ����Ѵ�.
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

/*
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
*/


// ���� �̹��� ������ 1024 ũ��� ������ ����ü�Դϴ�.
struct TempImageData {
	// ������ ������ ũ�Ⱑ ����˴ϴ�. ( 1024�� ���� �ʽ��ϴ�. )
	int size;
	// �̹����� ������ �޸��Դϴ�.
	char data[1024];
};

// ���̹����� CPtrList �� 1024 ������ ����� �����ϴ� �Լ��Դϴ�.
// ���Ź��� �̹����� ��ü ũ�⸦ ��ȯ�մϴ�.
DWORD CHearthstoneBotDlg::GetImageFromWeb(CPtrList *parm_list)	{
	// ���������� �̹����� ������, ��Ʈ�� ������ �߻��ϸ� ��� ��ٸ� �������� ����� 
	// �̺�Ʈ ��ü�� �����մϴ�.
	HANDLE h_wait_event = CreateEvent(NULL, TRUE, FALSE, "GIFW_01");
	DWORD total_size = 0;


	// ���ͳݿ� �ִ� ������ ����ϱ� ���ؼ� ������ �����Ѵ�.
	HINTERNET h_session = ::InternetOpen("Tipssoft Example", PRE_CONFIG_INTERNET_ACCESS, NULL, INTERNET_INVALID_PORT_NUMBER, 0);

	// www.tipssoft.com ����Ʈ�� ������ �մϴ�.
	HINTERNET h_connect = ::InternetConnect(h_session, "www.tipssoft.com", INTERNET_INVALID_PORT_NUMBER, "", "", INTERNET_SERVICE_HTTP, 0, 0);

	// ���ӵ� ����Ʈ���� Ư�� ��ο� �ִ� ������ ������ �ֵ��� ��û�Ѵ�. 
	// �׸��� ��θ� ����Ҷ��� ����Ʈ �ּҸ� ������ ������ ��θ� ����ϸ� �˴ϴ�.
	HINTERNET h_http_file = ::HttpOpenRequest(h_connect, "GET", "/img/logo.jpg", HTTP_VERSION, NULL, 0, INTERNET_FLAG_DONT_CACHE, 0);

	// ������ ������ ������ �����Ұ��� ��û�Ѵ�.
	BOOL request_flag = ::HttpSendRequest(h_http_file, NULL, 0, 0, 0);
	if(request_flag == TRUE){
		// �̹����� 1024ũ��� ������ ���� ����ü�� �����մϴ�.
		TempImageData *p_buffer = new TempImageData;
		char error_count = 0;
		DWORD read_byte = 0, buffer_size = 1024;


		// �ѹ��� �ִ� 1024 ũ�⸸ŭ ��Ʈ��ũ�� ���ؼ� �׸������� �����մϴ�.
		while(::InternetReadFile(h_http_file, p_buffer->data, buffer_size, &read_byte)){
			// ����� �������� ���ߴٸ� ����Ʈ�� �߰����� �ʽ��ϴ�.
			if(read_byte <= 0) delete p_buffer;
			else {
				// ��ü ũ�⿡ ���� ���ŵ� ũ�⸦ �ջ��մϴ�.
				total_size += read_byte;
				// 1����Ʈ�� �����ߴٸ� ����Ʈ�� �߰��մϴ�.
				p_buffer->size = read_byte;
				parm_list->AddTail(p_buffer);
			}


			// ���� 1024����Ʈ�� ������ ����ü�� �����մϴ�.
			p_buffer = new TempImageData;

			if(read_byte < 1024){
				// 1024 ���� ���� ��츦 ���� ���, ���� ���ؼ� ���д� ��쵵 �ֱ� ������
				// �ִ� 5������ ��õ��Ѵ�. ��õ��� �ϴ� ��� 50ms�� �����ð��� �ο��Ͽ�
				// ������ ��ٸ����� �Ѵ�.
				error_count++;
				if(error_count > 5) break;
				else ::WaitForSingleObject(h_wait_event, 50);
			} else error_count = 0;
		}


		delete p_buffer;


		// �׸��� �����ϱ� ���� ������ ������ �ݴ´�.
		::InternetCloseHandle(h_http_file); 
	}

	// ���ͳ��� ����ϱ� ���ؼ� ������ �ڵ�� ���� �ڵ��� �ݴ´�.
	::InternetCloseHandle(h_connect);
	::InternetCloseHandle(h_session);


	// �̺�Ʈ ��ü�� �����Ѵ�.
	CloseHandle(h_wait_event);

	// ��ü ���ŵ� ũ�⸦ ��ȯ�մϴ�.
	return total_size;
}

void CHearthstoneBotDlg::LoadImageToPtrList(CPtrList *parm_list, DWORD parm_total_size) {
	// �̹����� �Ѱ��� ��Ʈ������ ����� ���ؼ� �̹��� ��üũ��� �޸𸮸� �����մϴ�.
	HGLOBAL h_global = GlobalAlloc(GMEM_MOVEABLE, parm_total_size);
	if(NULL != h_global){
		// �ڵ� ���·� �Ҵ�� ���� �޸𸮸� ����ϱ� ���ؼ� ���� �����͸� ����ϴ�.
		char *p_data = (char *)GlobalLock(h_global);

		if(NULL != p_data){
			TempImageData *p_buffer = NULL;
			int current_pos = 0;

			while(!parm_list->IsEmpty()){
				// ����Ʈ�� ���ۿ� ����Ǿ� �ִ� ����ü�� ��� �ش� ���� �����մϴ�.
				p_buffer = (TempImageData *)parm_list->RemoveHead();


				// ���� ����ü�� ��Ʈ���� �߰��մϴ�.
				memcpy(p_data + current_pos, p_buffer->data, p_buffer->size);
				// �߰��� ��ġ�� �����մϴ�.
				current_pos += p_buffer->size;
				// ������, 1024�� ���� ���� �̹����� �����մϴ�.
				delete p_buffer;
			}


			GlobalUnlock(h_global);
		}


		LPSTREAM p_stream = NULL;
		// �о���� ���������� �̿��Ͽ� ��Ʈ�� ��ü�� �����մϴ�.
		HRESULT h_result = CreateStreamOnHGlobal(h_global, TRUE, &p_stream);
		if(SUCCEEDED(h_result) && p_stream){
			// ��Ʈ�� ��ü�� ������ �������� �׸�(Picture) ��ü�� �����մϴ�.
			// ������ �׸� ��ü�� �����ʹ� mp_image_object�� ����˴ϴ�.
			::OleLoadPicture(p_stream, parm_total_size, FALSE, IID_IPicture, (LPVOID *)&mp_image_object);
			// ��Ʈ�� ��ü�� �����մϴ�.
			p_stream->Release();

			if(SUCCEEDED(h_result) && mp_image_object){
				// �̹����� ���� ���� ũ�⸦ ����ϴ�.
				mp_image_object->get_Width(&m_logical_width);
				mp_image_object->get_Height(&m_logical_height);

				CClientDC dc(this);
				// ���� DC�� �µ��� ũ�⸦ �������մϴ�.
				m_real_width = MulDiv(m_logical_width, dc.GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH);
				m_real_height = MulDiv(m_logical_height, dc.GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH);

				// ȭ���� �����Ͽ� �׸��� �����ݴϴ�.
				InvalidateRect(m_display_rect);
			}
		}

		GlobalFree(h_global);
	}
}