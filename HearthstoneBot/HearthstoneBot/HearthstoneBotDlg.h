
// HearthstoneBotDlg.h : 헤더 파일
//

#pragma once
#include "webbrowser2.h"


// CHearthstoneBotDlg 대화 상자
class CHearthstoneBotDlg : public CDialogEx
{
private:
	LPPICTURE mp_image_object;
	long m_logical_width, m_logical_height, m_real_width, m_real_height;
	CRect m_display_rect;
// 생성입니다.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_HEARTHSTONEBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	void imageDown();

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void LoadImageToPtrList(CPtrList *parmList, DWORD parmTotalSize);
	DWORD GetImageFromWeb(CPtrList *parmList);

public:
	CExplorer1 m_my_browser;
};
