
// ExcelCal.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CExcelCalApp:
// �йش����ʵ�֣������ ExcelCal.cpp
//

class CExcelCalApp : public CWinApp
{
public:
	CExcelCalApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CExcelCalApp theApp;