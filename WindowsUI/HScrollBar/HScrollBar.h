
// HScrollBar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHScrollBarApp:
// �йش����ʵ�֣������ HScrollBar.cpp
//

class CHScrollBarApp : public CWinApp
{
public:
	CHScrollBarApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHScrollBarApp theApp;