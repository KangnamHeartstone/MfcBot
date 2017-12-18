
// HearthstoneBotDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "HearthstoneBot.h"
#include "HearthstoneBotDlg.h"
#include "afxdialogex.h"

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
	ON_WM_CLOSE()
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
	latestFileName = "";
	SearchLogFiles(GetCurrentUserNamePath());
	//RealtimeLogRead();
	CWinThread *pThread = AfxBeginThread(ThreadFirst, this);

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

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
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


CString CHearthstoneBotDlg::GetCurrentUserNamePath() {
	TCHAR username[UNLEN + 1];
	DWORD size = UNLEN + 1;
	GetUserName((TCHAR*)username, &size);
	char pathBuffer[MAX_BUFFER_SIZE] = {'\0', };
	char userName[UNLEN + 1] = {'\0', };

	WideCharToMultiByte(CP_ACP, 0, username, UNLEN + 1, userName, UNLEN + 1, NULL, NULL);
	printf("current user name: %s\n", userName);
	sprintf(pathBuffer, "C:\\Users\\%s\\AppData\\Local\\Blizzard\\Hearthstone\\Logs\\", userName);
	wcout << "log saved path: " << pathBuffer << endl;

	CString path = CString(pathBuffer);
	return path;
}

void CHearthstoneBotDlg::SearchLogFiles(CString absolutePath) {
	wcout << "searching path: " << absolutePath.GetString() << endl;
	CFileFind fileFinder;

	BOOL fileAvailable = fileFinder.FindFile(absolutePath + "*.log");

	if(fileAvailable) {
		printf("there is some files\n");

		while(fileAvailable) {
			fileAvailable = fileFinder.FindNextFile();

			if(fileFinder.IsArchived()) {
				CString fileName =  fileFinder.GetFileName();

				wcout << "file name: " << fileName.GetString() << endl;
				latestFileName = absolutePath + fileName;
			}
		}

		printf("search end\n");
	}
	else {
		printf("cannot see any file\n");
	}

	wcout << "latest file path: " << latestFileName.GetString() << endl;
}

UINT CHearthstoneBotDlg::ThreadFirst(LPVOID paramas) {
	CHearthstoneBotDlg *currentDlg = (CHearthstoneBotDlg *)paramas;
	printf("==========read log data===========\n");
	if(currentDlg->latestFileName != "") {
		ifstream ifs(currentDlg->latestFileName);	
		if (ifs.is_open())
		{
			std::string line;
			while (currentDlg->running)
			{/*
			 while (getline(ifs, line)) {
			 CString logData(line.c_str());
			 wcout << logData.GetString() << endl;
			 DetectFieldCard(logData);
			 DetectTurns(logData);
			 }*/
				char c;
				CString buffer;
				while(ifs.get(c)) {
					buffer = buffer + CString(c);
					if(c == '\n') {
						break;
					}
				}
				CString logData = buffer;
				currentDlg->DetectFieldCard(logData);
				currentDlg->DetectTurns(logData);
				//if (!ifs.eof()) break; // Ensure end of read was EOF.
				ifs.clear();
				Sleep(1);
				// You may want a sleep in here to avoid
				// being a CPU hog.
			}
		}
	}
	printf("end of read log\n");
	return 0;
}

void CHearthstoneBotDlg::RealtimeLogRead() {
	printf("==========read log data===========\n");
	if(latestFileName != "") {
		ifstream ifs(latestFileName);	
		if (ifs.is_open())
		{
			std::string line;
			while (true)
			{/*
			 while (getline(ifs, line)) {
			 CString logData(line.c_str());
			 wcout << logData.GetString() << endl;
			 DetectFieldCard(logData);
			 DetectTurns(logData);
			 }*/
				char c;
				CString buffer;
				while(ifs.get(c)) {
					buffer = buffer + CString(c);
					if(c == '\n') {
						break;
					}
				}
				CString logData = buffer;
				DetectFieldCard(logData);
				DetectTurns(logData);
				//if (!ifs.eof()) break; // Ensure end of read was EOF.
				ifs.clear();

				// You may want a sleep in here to avoid
				// being a CPU hog.
			}
		}
	}
	printf("end of read log\n");
}

void CHearthstoneBotDlg::DetectFieldCard(CString logMessage) {
	CString entity, value, zonePosition, cardId, player;
	entity = GetSubStringPattern(logMessage, CString("TAG_CHANGE Entity="), CString(" tag=NUM_TURNS_IN_PLAY value="));
	value = GetSubStringPattern(logMessage, CString(" tag=NUM_TURNS_IN_PLAY value="), CString(" \n"));
	if(!entity.IsEmpty() && !value.IsEmpty()) {
		zonePosition = GetSubStringPattern(entity, CString(" zonePos="), CString(" cardId="));
		cardId = GetSubStringPattern(entity, CString(" cardId="), CString(" player="));
		player = GetSubStringPattern(entity, CString(" player="), CString("]"));
		wcout << "[DetectFieldCard] entity zonePos: " << zonePosition.GetString() << " card id: " << cardId.GetString() << " player: " << player.GetString() << " val: " << value.GetString() << endl;
		if(!zonePosition.IsEmpty() && !cardId.IsEmpty() && !player.IsEmpty()) {
			int playerNumber = _ttoi(player), zonePositionNumber = _ttoi(zonePosition);
			fieldCard[(playerNumber - 1) * 8 + zonePositionNumber].SetCardID(cardId);
		}
	}
}

void CHearthstoneBotDlg::DetectTurns(CString logMessage) {
	CString entity, value;
	entity = GetSubStringPattern(logMessage, CString("TAG_CHANGE Entity="), CString(" tag=STEP value="));
	value = GetSubStringPattern(logMessage, CString(" tag=STEP value="), CString(" \n"));
	if(!entity.IsEmpty() && !value.IsEmpty()) {
		wcout << "[DetectTurns] val: " << value.GetString() << endl;
		if(value.Compare(CString("MAIN_START_TRIGGERS")) == CSTRING_EQUAL) {
			wcout << "[DetectTurns] end of tracking field" << endl;
			PrintFieldPretty();
		}
		else if(value.Compare(CString("MAIN_READY")) == CSTRING_EQUAL) {
			wcout << "[DetectTurns] rdy for tracking field" << endl;
			int i;
			for(i = 0; i < SIZE_OF_FIELD; i += 1) {
				fieldCard[i].SetAttack(0);
				fieldCard[i].SetCardID(CString(""));
				fieldCard[i].SetCardName(CString(""));
				fieldCard[i].SetHealth(0);
			}
		}
	}
}

void CHearthstoneBotDlg::PrintFieldPretty() {
	int i;
	for(i = 0; i < SIZE_OF_FIELD / 2; i += 1) {
		wcout << setw(9) << setfill(L' ') << fieldCard[i].GetCardID().GetString() << "|";
	}
	cout << endl;
	for(i = SIZE_OF_FIELD / 2; i < SIZE_OF_FIELD; i += 1) {
		wcout << setw(9) << setfill(L' ') << fieldCard[i].GetCardID().GetString() << "|";
	}
	cout << endl;
}

CString CHearthstoneBotDlg::GetSubStringPattern(CString logMessage, CString target, CString nonTarget) {
	CString result;
	int targetStartPoint = 0, nonTargetStartPoint = 0, logMessageLen = 0;
	int targetLength = 0, nonTargetLength = 0;
	targetStartPoint = logMessage.Find(target);
	if(nonTarget.IsEmpty()) {
		nonTargetStartPoint = logMessage.GetLength();
	}
	else {
		nonTargetStartPoint = logMessage.Find(nonTarget);
	}
	if(targetStartPoint == NOT_AVAILABLE || nonTargetStartPoint == NOT_AVAILABLE) {
		return NULL;
	}

	logMessageLen = logMessage.GetLength();
	targetLength = target.GetLength();
	nonTargetLength = nonTarget.GetLength();

	result = logMessage.Mid(targetStartPoint + targetLength, nonTargetStartPoint - (targetStartPoint + targetLength));
	return result;
}

void CHearthstoneBotDlg::OnClose()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	running = false;
	CDialogEx::OnClose();
}
