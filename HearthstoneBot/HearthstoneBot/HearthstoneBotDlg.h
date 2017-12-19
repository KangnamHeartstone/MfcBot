
// HearthstoneBotDlg.h : ��� ����
//

#pragma once


// CHearthstoneBotDlg ��ȭ ����
class CHearthstoneBotDlg : public CDialogEx
{
private:
	// �̹��� ��ü�� �����͸� ������ ����
	LPPICTURE mp_image_object;
	// �о���� �̹����� ���� ���̿� ���� ũ�� ����
	long m_logical_width, m_logical_height, m_real_width, m_real_height;

	// �׸��� ���� ��µ� ��ġ�� ����� ����
	CRect m_display_rect;


// �����Դϴ�.
public:
	CHearthstoneBotDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_HEARTHSTONEBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.
	void imageDown();

// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void LoadImageToPtrList(CPtrList *parmList, DWORD parmTotalSize);
	DWORD GetImageFromWeb(CPtrList *parmList);

public:
};
