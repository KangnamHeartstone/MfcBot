
// HearthstoneBot.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CHearthstoneBotApp:
// �� Ŭ������ ������ ���ؼ��� HearthstoneBot.cpp�� �����Ͻʽÿ�.
//

class CHearthstoneBotApp : public CWinApp
{
public:
	CHearthstoneBotApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CHearthstoneBotApp theApp;