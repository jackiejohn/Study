// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <tchar.h>
#include <locale.h>

int _tmain(int argc, _TCHAR* argv[])
{
    FILE* fp = nullptr;
    errno_t err = _tfopen_s(&fp, L"D:\\test\\testun.txt", L"a+,ccs=UNICODE");
    TCHAR* p = L"abc��\r\n";
    int len = _tcslen(p);
    fwrite(p, 2, len, fp);
    fclose(fp);
	return 0;
}

