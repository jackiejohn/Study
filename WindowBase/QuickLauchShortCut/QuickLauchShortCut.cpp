// QuickLauchShortCut.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <shlobj.h>
#include <string>
#include <assert.h>

typedef std::wstring AnsiString;
#define EmptyStr L""
// �������з��ڵ�Ԫ�ļ��ʼ
//---------------------------------------------------------------------------
struct TShortcutCfg
{
    // ���캯��
    TShortcutCfg()
    {
        nShowCmd = SW_SHOWNORMAL;
        wHotKey = 0;
        nIconIndex = 0;
    }
    // �ṹ��Ա:
    AnsiString  strShortcutName; //
    AnsiString  strLnkDir;       //
    AnsiString  strDestFile;     //
    AnsiString  strArguments;    //
    AnsiString  strIconFile;     //
    int         nIconIndex;      //
    AnsiString  strWorkingDir;   //
    AnsiString  strDescription;  //
    WORD        wHotKey;         //
    int         nShowCmd;        //
};
//---------------------------------------------------------------------------
// �ڿ���������������ݷ�ʽ
bool CreateQuickLaunchShortcut(TShortcutCfg *scConfig)
{
    TCHAR szBuf[MAX_PATH];
    bool bReturn = true;
    HRESULT hr = S_FALSE;
    IShellLink *pShellLink;
    AnsiString strShortcutFile;
    LPITEMIDLIST lpItemIdList;
    SHGetSpecialFolderLocation(0, CSIDL_APPDATA, &lpItemIdList);
    SHGetPathFromIDList(lpItemIdList, szBuf);
     strShortcutFile = AnsiString(szBuf)
            + L"\\Microsoft\\Internet Explorer\\Quick Launch\\"
            + scConfig->strShortcutName + L".lnk";
     CoTaskMemFree(lpItemIdList);

    if (bReturn)
    {
        HRESULT hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                                   IID_IShellLink, (void **)&pShellLink);
        if (SUCCEEDED(hr))
        {
            IPersistFile *ppf;
            hr = pShellLink->QueryInterface(IID_IPersistFile, (void **)&ppf);
            if (SUCCEEDED(hr))
            {
                // Ŀ���ļ�
                if (!scConfig->strDestFile.empty())
                    hr = pShellLink->SetPath(scConfig->strDestFile.c_str());
                // ����
                if (SUCCEEDED(hr) && scConfig->strArguments != EmptyStr)
                    hr = pShellLink->SetArguments(scConfig->strArguments.c_str());
                // ��ʾͼ��
                if (SUCCEEDED(hr) && scConfig->strIconFile != EmptyStr)
                    pShellLink->SetIconLocation(scConfig->strIconFile.c_str(),
                    scConfig->nIconIndex);
                 // ��ʼλ��
                if (SUCCEEDED(hr) && scConfig->strWorkingDir != EmptyStr)
                    pShellLink->SetWorkingDirectory(scConfig->strWorkingDir.c_str());
                // ��ע
                if (SUCCEEDED(hr) && scConfig->strDescription != EmptyStr)
                    pShellLink->SetDescription(scConfig->strDescription.c_str());
                // ��ݼ�
                if (SUCCEEDED(hr) && scConfig->wHotKey != 0)
                    pShellLink->SetHotkey(scConfig->wHotKey);
                // ���з�ʽ
                if (SUCCEEDED(hr) && scConfig->nShowCmd != 0)
                    pShellLink->SetShowCmd(scConfig->nShowCmd);

                hr = ppf->Save(strShortcutFile.c_str(), TRUE);
                assert(SUCCEEDED(hr));
                ppf->Release();
            }
            pShellLink->Release();
        }
    }
    return (bReturn && SUCCEEDED(hr));
}
// ���ô��������
//---------------------------------------------------------------------------
void Button1Click()
{
    TShortcutCfg scShortcut;
    scShortcut.strDestFile = L"D:\\Test\\test.txt";
    scShortcut.strShortcutName = L"test";
    if (CreateQuickLaunchShortcut(&scShortcut))
        OutputDebugString(L"�ڿ���������������ݷ�ʽ�ɹ�!");
}
int _tmain(int argc, _TCHAR* argv[])
{
    ::CoInitialize(0);
    Button1Click();
    ::CoUninitialize();
	return 0;
}

