
// HearthstoneBotDlg.h : ��� ����
//
#include <windows.h>
#include <Lmcons.h>
#include <iostream>

#pragma once

// CHearthstoneBotDlg ��ȭ ����
class CHearthstoneBotDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HEARTHSTONEBOT_DIALOG };
	void ReadLogRealtime();
	char *GetCurrentUserName();
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
};
