
// TestOther.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestOtherApp: 
// �йش����ʵ�֣������ TestOther.cpp
//

class CTestOtherApp : public CWinApp
{
public:
	CTestOtherApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTestOtherApp theApp;