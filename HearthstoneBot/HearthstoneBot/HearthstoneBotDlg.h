
// HearthstoneBotDlg.h : 헤더 파일
//
#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <codecvt>
#include <iomanip>
#include <vector>
#include "json/json.h"
#include "CardData.h"
#include "cwebbrowser2.h"
#include "Wininet.h"
#include "afxwin.h"

#pragma comment(lib, "json/json_vc71_libmtd.lib")

using namespace std;

#define READ_BUF_SIZE 1024
#define MAX_BUFFER_SIZE 512
#define NOT_AVAILABLE -1
#define CSTRING_EQUAL 0
#define SIZE_OF_FIELD 16
#define CARD_JSON_FILE "res/CardInfo.json"
#define JSON_BUFFER_SIZE 3000000
#define FIELD_LINE_SIZE 8
#pragma once

// CHearthstoneBotDlg 대화 상자
class CHearthstoneBotDlg : public CDialogEx
{
// 생성입니다.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
	CString latestFileName;
	BOOL running;
	CardData fieldCard[SIZE_OF_FIELD];
	Json::Reader jsonReader;
	Json::Value jsonRoot;
	BOOL startCalculate;
	int fieldAttackInfo[2][FIELD_LINE_SIZE];
	int bestFieldAttackInfo[2][FIELD_LINE_SIZE];

	CImage enemyImages[7];
	CImage myCardImages[7];
	//char readBuffer[JSON_BUFFER_SIZE];
// 대화 상자 데이터입니다.
	int getFileFromHttp(char* pszUrl, char* pszFile);
	static UINT ThreadFirst(LPVOID paramas);
	enum { IDD = IDD_HEARTHSTONEBOT_DIALOG };
	void ReadLogRealtime();
	CString GetCurrentUserNamePath();
	void SearchLogFiles(CString );
	void RealtimeLogRead();
	void DetectFieldCard(CString );
	void DetectTurns(CString );
	CString GetSubStringPattern(CString, CString, CString = CString(""));
	void PrintFieldPretty();
	void SearchCardData(CString cardData, CardData &);
	CString ReadJsonAsString();
	bool ReadFromFile(const char* filename, char* buffer, int len);
	void InitJsonLoader();
	void CalculateRunner();
	void RecursiveSetAttackTarget(int, int);
	int PredictCardSwap(int );
	void cardOutput();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	CStatic enemyCard1;
	CStatic enemyCard2;
	CStatic enemyCard3;
	CStatic enemyCard4;
	CStatic enemyCard5;
	CStatic enemyCard6;
	CStatic enemyCard7;
	CStatic myCard1;
	CStatic myCard2;
	CStatic myCard3;
	CStatic myCard4;
	CStatic myCard5;
	CStatic myCard6;
	CStatic myCard7;
};
