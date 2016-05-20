// PreReadDisk.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string>
#include <windows.h>
#include <sstream>
#include <assert.h>

void PreReadFile(const std::wstring& path, std::wstring* out)
{
    HANDLE hFile = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ,
                              nullptr, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN,
                              nullptr);
    assert(hFile);
    int len = 1000 * 1000;
    TCHAR* buf = new TCHAR[len];
    DWORD readFinally = 0;
    BOOL ret = FALSE;
    do 
    {
        ret = ReadFile(hFile, buf, len, &readFinally, NULL);
        if (out && ret && readFinally)
        {
            out->append(buf, readFinally);
        }
    } while (ret && readFinally);
    delete [] buf;
    CloseHandle(hFile);
}

void PreReadDiskUseTime()
{
    // ��ʵ֤���� ���ȶ�һ�ε�ȷ����´ζ��ļ���ʱ�䣬 ��1482 ���˵͵� 682
    PreReadFile(L"D:\\Kugou\\ͯ�� - ������¥.ape", nullptr);
    PreReadFile(L"D:\\Kugou\\������ - ���.ape", nullptr);
    PreReadFile(L"D:\\Kugou\\������ - �������ڷ����.ape", nullptr);
    PreReadFile(L"D:\\Kugou\\֣�ڡ�Ѧ���� - ���̵�.ape", nullptr);
    //Sleep(3000);
    std::wstring text;
    DWORD beg = GetTickCount();
    PreReadFile(L"D:\\Kugou\\ͯ�� - ������¥.ape", &text);
    PreReadFile(L"D:\\Kugou\\������ - ���.ape", &text);
    PreReadFile(L"D:\\Kugou\\������ - �������ڷ����.ape", &text);
    PreReadFile(L"D:\\Kugou\\֣�ڡ�Ѧ���� - ���̵�.ape", &text);
    DWORD end = GetTickCount();
    std::wstringstream ss;
    ss << L"ʹ���˶���ʱ��: " << end - beg << L"\n";
    std::wstring output = ss.str();
    setlocale(LC_ALL, "chs");
    printf("Use:: %ls", output.c_str());
}


int _tmain(int argc, _TCHAR* argv[])
{
    PreReadDiskUseTime();
    system("pause");
    PreReadFile(L"E:\\0��������\\HIFI\\FormatSound\\wong.wing.tsan.������.-��կ��.ˮ֮��.ɭ֮��.ר��.tta", NULL);
    PreReadFile(L"E:\\0��������\\HIFI\\FormatSound\\Daniel Shafran - Kabalevsky-Davidov-Tchaikovsky.wv", NULL);
	return 0;
}

