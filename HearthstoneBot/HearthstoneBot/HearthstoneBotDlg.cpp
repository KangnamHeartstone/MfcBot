
// HearthstoneBotDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "HearthstoneBot.h"
#include "HearthstoneBotDlg.h"
#include "afxdialogex.h"

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
	DDX_Control(pDX, IDC_EXPLORER2, m_card1);
	DDX_Control(pDX, IDC_EXPLORER3, m_card2);
}

BEGIN_MESSAGE_MAP(CHearthstoneBotDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
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
	latestFileName = "";
	startCalculate = false;
	SearchLogFiles(GetCurrentUserNamePath());
	//RealtimeLogRead();
	InitJsonLoader();
	CWinThread *pThread = AfxBeginThread(ThreadFirst, this);

	cardOutput();

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

void CHearthstoneBotDlg::cardOutput() {
	CString cardName = _T("http://media.services.zam.com/v1/media/byName/hs/cards/enus/animated/HERO_01_premium.gif");

	CComVariant var(cardName);
	m_card1.Navigate2(&var, NULL, NULL, NULL, NULL);
}

void CHearthstoneBotDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	running = false;
	CDialogEx::OnClose();
}