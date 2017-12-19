
// HearthstoneBotDlg.h : 헤더 파일
//

#pragma once


// CHearthstoneBotDlg 대화 상자
class CHearthstoneBotDlg : public CDialogEx
{
private:
	// 이미지 객체의 포인터를 저장할 변수
	LPPICTURE mp_image_object;
	// 읽어들인 이미지의 폭과 높이에 대한 크기 정보
	long m_logical_width, m_logical_height, m_real_width, m_real_height;

	// 그림이 실제 출력될 위치를 기억할 변수
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
};
