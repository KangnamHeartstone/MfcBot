
// HearthstoneBotDlg.h : ��� ����
//
#include <windows.h>
#include <Lmcons.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <codecvt>
#include "CardData.h"

using namespace std;

#define MAX_BUFFER_SIZE 512
#define NOT_AVAILABLE -1
#pragma once

// CHearthstoneBotDlg ��ȭ ����
class CHearthstoneBotDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CString latestFileName;
	BOOL running;
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
