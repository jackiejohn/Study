// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../../Include/XLogger.h"
#pragma comment(lib, "../../Output/lib/Debug32/XLogger.lib")


int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitialize(0);

    XLOGGER_OPEN;
    {
        XLOGGER_DEBUG(L"hi");
    }

    ::CoUninitialize();
	return 0;
}

