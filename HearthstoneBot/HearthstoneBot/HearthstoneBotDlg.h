
// HearthstoneBotDlg.h : ��� ����
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

#pragma comment(lib, "json/json_vc71_libmtd.lib")

using namespace std;

#define MAX_BUFFER_SIZE 512
#define NOT_AVAILABLE -1
#define CSTRING_EQUAL 0
#define SIZE_OF_FIELD 16
#define CARD_JSON_FILE "res/CardInfo.json"
#define JSON_BUFFER_SIZE 3000000
#pragma once

// CHearthstoneBotDlg ��ȭ ����
class CHearthstoneBotDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CString latestFileName;
	BOOL running;
	CardData fieldCard[SIZE_OF_FIELD];
	Json::Reader jsonReader;
	Json::Value jsonRoot;
	BOOL startCalculate;
	//char readBuffer[JSON_BUFFER_SIZE];
// ��ȭ ���� �������Դϴ�.
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
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
