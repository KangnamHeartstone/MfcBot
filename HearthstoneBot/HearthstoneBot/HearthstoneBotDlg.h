
// HearthstoneBotDlg.h : ��� ����
//

#pragma once


// CHearthstoneBotDlg ��ȭ ����
class CHearthstoneBotDlg : public CDialogEx
{
private:
	LPPICTURE mp_image_object;
	long m_logical_width, m_logical_height, m_real_width, m_real_height;
	CRect m_display_rect;
// �����Դϴ�.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HEARTHSTONEBOT_DIALOG };

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
