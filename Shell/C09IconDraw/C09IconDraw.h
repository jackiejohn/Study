
// C09IconDraw.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CC09IconDrawApp:
// �йش����ʵ�֣������ C09IconDraw.cpp
//

class CC09IconDrawApp : public CWinApp
{
public:
	CC09IconDrawApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CC09IconDrawApp theApp;