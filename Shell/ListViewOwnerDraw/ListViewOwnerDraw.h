
// ListViewOwnerDraw.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CListViewOwnerDrawApp:
// �йش����ʵ�֣������ ListViewOwnerDraw.cpp
//

class CListViewOwnerDrawApp : public CWinApp
{
public:
	CListViewOwnerDrawApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CListViewOwnerDrawApp theApp;