// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>


int _tmain(int argc, _TCHAR* argv[])
{

    DWORD value = 0x11225566;
    WORD lo = LOWORD(value);
    WORD hi = HIWORD(value);
    WORD loTest = value & 0xFFFF;
    WORD hiTest = value >> 16;
	return 0;
}

