// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// ĳЩ CString ���캯��������ʽ��

#ifndef UNICODE
#error "*** ���붨��UNICODE�ַ���!!!! ***"
#endif

#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlstr.h>
#include <atlcoll.h>
#include <share.h>
#include <atltime.h>

using namespace ATL;
using namespace std;

#define WRITE_SIMPLE_LOGGER
#include "..\Logger\SimpleLogger.h"

#define MAX_SERVER_COUNT         100

class CTimeInfo
{
	DWORD Time;
	char FileName[MAX_PATH];
	char Function[MAX_PATH * 2];
	int  FileLine;
public:
	CTimeInfo(const char *funct, const char *file, int line) {
		ATLASSERT(NULL != file);
		ATLASSERT(NULL != funct);
		UINT Length = (UINT)strnlen(file, MAX_PATH - 1);
		memcpy(FileName, file, Length);
		FileName[Length] = 0;
		Length = (UINT)strnlen(funct, MAX_PATH * 2 - 1);
		memcpy(Function, funct, Length);
		Function[Length] = 0;
		FileLine = line;
		Time     = GetTickCount();
	}
	~CTimeInfo() {
		DWORD End = GetTickCount();
		if ((End - Time) > 60)
		{
			LOGGER_WRITE2_A("�߳�:" << GetCurrentThreadId()
				<< " ��ʱ:" << (End - Time) 
				<< " " << Function 
				<< " " << FileName 
				<< " " << FileLine);
		}
	}
};
#ifdef _DEBUG
#define USING_TIME_INFO CTimeInfo Time##__LINE__##(__FUNCTION__, __FILE__, __LINE__);
#else
#define USING_TIME_INFO CTimeInfo Time##__LINE__##(__FUNCTION__, __FILE__, __LINE__);
#endif