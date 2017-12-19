
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
	startCalculate = false;
	SearchLogFiles(GetCurrentUserNamePath());
	//RealtimeLogRead();
	InitJsonLoader();
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

void CHearthstoneBotDlg::CalculateRunner() {
	cout << "=============Calculate field=============" << endl;
	int i, t, playerNumber = 0;
	for(i = 0; i < 2;i += 1) {
		for(t = 0; t < FIELD_LINE_SIZE; t += 1) {
			fieldAttackInfo[i][t] = NOT_AVAILABLE;
			bestFieldAttackInfo[i][t] = NOT_AVAILABLE;
		}
	}

	bestFieldAttackInfo[0][0] = -987654321;
	bestFieldAttackInfo[1][0] = -987654321;

	cout << "=============Player #" << playerNumber << "=============" << endl;
	RecursiveSetAttackTarget(0, playerNumber);
	
	playerNumber = (playerNumber + 1) % 2;

	cout << "=============Player #" << playerNumber << "=============" << endl;
	RecursiveSetAttackTarget(0, playerNumber);
	
	playerNumber = (playerNumber + 1) % 2;

	cout << "=============Best card swap #" << playerNumber << "=============" << endl;
	for(i = 0; i < FIELD_LINE_SIZE; i += 1) {
		cout << setw(3) << setfill(' ') << bestFieldAttackInfo[playerNumber][i] << "|" ;
	}
	cout << endl;
	
	playerNumber = (playerNumber + 1) % 2;

	cout << "=============Best card swap#" << playerNumber << "=============" << endl;
	for(i = 0; i < FIELD_LINE_SIZE; i += 1) {
		cout << setw(3) << setfill(' ') << bestFieldAttackInfo[playerNumber][i] << "|" ;
	}
	cout << endl;
}

int CHearthstoneBotDlg::PredictCardSwap(int playerNumber) {
	int enemyNumber = (playerNumber + 1) % 2, i, positiveSum = 0, negativeSum = 0, enemyAliveNum = 0;
	CardData fieldCardSwap[SIZE_OF_FIELD];
	for(i = 0; i < SIZE_OF_FIELD; i += 1) {
		fieldCardSwap[i] = fieldCard[i];
	}
	for(i = 1; i < FIELD_LINE_SIZE; i += 1) {
		if(fieldAttackInfo[playerNumber][i] > 0) {//if player card, attack target selected
			int attackEnemyCard = enemyNumber * FIELD_LINE_SIZE + fieldAttackInfo[playerNumber][i];
			int attackPlayerCard = playerNumber * FIELD_LINE_SIZE + i;
			if(fieldCardSwap[attackEnemyCard].GetHealth() > 0) {// attack target health > 0
				fieldCardSwap[attackEnemyCard].SetHealth(fieldCardSwap[attackEnemyCard].GetHealth() - fieldCardSwap[attackPlayerCard].GetAttack());
				fieldCardSwap[attackPlayerCard].SetHealth(fieldCardSwap[attackPlayerCard].GetHealth() - fieldCardSwap[attackEnemyCard].GetAttack());
			}
		}
	}

	for(i = 1; i < FIELD_LINE_SIZE; i += 1) {
		if(!fieldCardSwap[playerNumber * FIELD_LINE_SIZE + i].GetCardID().IsEmpty()) {
			int health = fieldCardSwap[playerNumber * FIELD_LINE_SIZE + i].GetHealth();
			if(health < 0) {
				health = 0;
			}
			positiveSum = positiveSum + health;
		}
		if(!fieldCardSwap[enemyNumber * FIELD_LINE_SIZE + i].GetCardID().IsEmpty()) {
			int health = fieldCardSwap[enemyNumber * FIELD_LINE_SIZE + i].GetHealth();
			if(health > 0) {
				negativeSum = negativeSum + fieldCardSwap[enemyNumber * FIELD_LINE_SIZE + i].GetAttack();
				enemyAliveNum = enemyAliveNum + 1;
			}
		}
	}

	return positiveSum - negativeSum - enemyAliveNum;
}

void CHearthstoneBotDlg::RecursiveSetAttackTarget(int level, int playerNumber) {
	int nowFocusIndex = playerNumber * FIELD_LINE_SIZE + level, i, enemyNumber = (playerNumber + 1) % 2, score;
	if(level >= FIELD_LINE_SIZE) {
		/*for(i = 0; i < FIELD_LINE_SIZE; i += 1) {
			cout << setw(3) << setfill(' ') << fieldAttackInfo[playerNumber][i] << "|" ;
		}*/
		score = PredictCardSwap(playerNumber);
		//cout << " <--- " << score ;
		if(bestFieldAttackInfo[playerNumber][0] < score) {
			bestFieldAttackInfo[playerNumber][0] = score;
			//cout << " new best";
			for(i = 1; i < FIELD_LINE_SIZE; i += 1) {
				bestFieldAttackInfo[playerNumber][i] = fieldAttackInfo[playerNumber][i];
			}
		}
		//cout << endl;
		return;
	}

	if(!fieldCard[nowFocusIndex].GetCardID().IsEmpty() && level != 0) {//player not empty
		for(i = 0; i < FIELD_LINE_SIZE; i += 1) {
			if(!fieldCard[enemyNumber * FIELD_LINE_SIZE + i].GetCardID().IsEmpty()) { //enemy not empty
				fieldAttackInfo[playerNumber][level] = i;
				RecursiveSetAttackTarget(level + 1, playerNumber);
			}
		}
	}
	else {
		RecursiveSetAttackTarget(level + 1, playerNumber);
	}
	fieldAttackInfo[playerNumber][level] = NOT_AVAILABLE;
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
				if(currentDlg->startCalculate) {
					// start calculate
					currentDlg->startCalculate = false;
					currentDlg->CalculateRunner();
				}
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

CString CHearthstoneBotDlg::ReadJsonAsString() {
	CFile file;
	CString jsonData;
	if(file.Open(CString(CARD_JSON_FILE), CFile::modeRead | CFile::typeBinary))
	{
		int len = file.GetLength();
		file.Read(jsonData.GetBuffer(len), len);
		jsonData.ReleaseBuffer();
	}
	return jsonData;
}

bool CHearthstoneBotDlg::ReadFromFile(const char* filename, char* buffer, int len) {
	FILE* fp = nullptr;
	fopen_s(&fp ,filename, "rb");
	if (fp == nullptr) 
	{
		return false;
	}
	size_t fileSize = fread(buffer, 1, len, fp);
	fclose(fp);
	return true;
}

void CHearthstoneBotDlg::InitJsonLoader() {

	ifstream cardJsonFile(CARD_JSON_FILE);
	cardJsonFile >> jsonRoot;

	int rootCategorySize = jsonRoot.size();
	cout << "===========json loader===========" << endl;
	cout << "root size: " << rootCategorySize << endl;
	int i;
	vector<string> rootJsonMembers = jsonRoot.getMemberNames();
	for(i = 0; i < rootJsonMembers.size(); i += 1) {
		cout << "cate #" << i << " : " << rootJsonMembers[i] << endl;
	}
	cout << "=================================" << endl;
}

void CHearthstoneBotDlg::SearchCardData(CString cardId, CardData &savePoint) {
	vector<string> rootJsonMembers = jsonRoot.getMemberNames();
	int i, t;
	bool endOfSearch = false;
	for(i = 0; i < rootJsonMembers.size(); i += 1) {
		Json::Value indexOfSeries = jsonRoot[rootJsonMembers[i]];
		//cout << "Series of " << rootJsonMembers[i] << " size: " << indexOfSeries.size() << endl;
		for(t = 0; t < indexOfSeries.size(); t += 1) {
			string indexOfCardIdStr = indexOfSeries[t].get("cardId", "").asCString();
			CString indexOfCardId(indexOfCardIdStr.c_str());
			if(cardId.Compare(indexOfCardId) == CSTRING_EQUAL) {
				endOfSearch = true;
				int attack, health;
				CString imgUrl, name;

				attack = indexOfSeries[t].get("attack", NOT_AVAILABLE).asInt();
				health = indexOfSeries[t].get("health", NOT_AVAILABLE).asInt();
				imgUrl = indexOfSeries[t].get("img", "").asCString();
				name = indexOfSeries[t].get("name", "").asCString();

				savePoint.SetAttack(attack);
				savePoint.SetCardName(name);
				savePoint.SetHealth(health);
				savePoint.SetImgUrl(imgUrl);
				break;
			}
		}
		if(endOfSearch) {
			break;
		}
	}
}

void CHearthstoneBotDlg::DetectFieldCard(CString logMessage) {
	CString entity, value, zonePosition, cardId, player;
	entity = GetSubStringPattern(logMessage, CString("TAG_CHANGE Entity="), CString(" tag=NUM_TURNS_IN_PLAY value="));
	value = GetSubStringPattern(logMessage, CString(" tag=NUM_TURNS_IN_PLAY value="), CString(" \n"));
	if(!entity.IsEmpty() && !value.IsEmpty()) {
		zonePosition = GetSubStringPattern(entity, CString(" zonePos="), CString(" cardId="));//HERO_01
		cardId = GetSubStringPattern(entity, CString(" cardId="), CString(" player="));
		player = GetSubStringPattern(entity, CString(" player="), CString("]"));
		wcout << "[DetectFieldCard] entity zonePos: " << zonePosition.GetString() << " card id: " << cardId.GetString() << " player: " << player.GetString() << " val: " << value.GetString() << endl;
		if(!zonePosition.IsEmpty() && !cardId.IsEmpty() && !player.IsEmpty()) {
			int playerNumber = _ttoi(player), zonePositionNumber = _ttoi(zonePosition);
			fieldCard[(playerNumber - 1) * 8 + zonePositionNumber].SetCardID(cardId);

			CString searchTargetId = fieldCard[(playerNumber - 1) * 8 + zonePositionNumber].GetCardID();
			SearchCardData(searchTargetId, fieldCard[(playerNumber - 1) * 8 + zonePositionNumber]);
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
			startCalculate = true;
		}
		else if(value.Compare(CString("MAIN_READY")) == CSTRING_EQUAL) {
			wcout << "[DetectTurns] rdy for tracking field" << endl;
			int i;
			for(i = 0; i < SIZE_OF_FIELD; i += 1) {
				fieldCard[i].SetAttack(NOT_AVAILABLE);
				fieldCard[i].SetCardID(CString(""));
				fieldCard[i].SetCardName(CString(""));
				fieldCard[i].SetImgUrl(CString(""));
				fieldCard[i].SetHealth(NOT_AVAILABLE);
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