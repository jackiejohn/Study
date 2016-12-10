// PropPage.cpp : CPropPage ��ʵ��

#include "stdafx.h"
#include "PropPage.h"
TCHAR g_szFile[MAX_PATH];

// CPropPage

HRESULT CPropPage::Initialize(LPCITEMIDLIST pidlFolder, LPDATAOBJECT

    lpdobj, HKEY hKeyProgID)

{
    MessageBox(nullptr, L"CPropPage::Initialize", L"CPropPage::Initialize", MB_OK);

    if(lpdobj == NULL)

        return E_INVALIDARG;

    // ��ʼ��ͨ�ÿؼ�(����ҳ��ͨ�ÿؼ�)

    InitCommonControls();

    // ��IDataObject���ѡ���ļ�����������CF_HDROP��ʽ�洢

    STGMEDIUM medium;

    FORMATETC fe = {CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL};

    HRESULT hr = lpdobj->GetData(&fe, &medium);

    if(FAILED(hr))

        return E_INVALIDARG;

    HDROP hDrop = static_cast<HDROP>(medium.hGlobal);

    if(DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0) == 1)

    {

        DragQueryFile(hDrop, 0, m_szFile, sizeof(m_szFile));

        hr = NOERROR;

    }else

        hr = E_INVALIDARG;

    ReleaseStgMedium(&medium);

    return hr;

}

int g_cnt = 1;

HRESULT CPropPage::AddPages(LPFNADDPROPSHEETPAGE lpfnAddPage, LPARAM lParam)

{

    lstrcpy(g_szFile, m_szFile);

    // ������ҳ����Ҫ���PROPSHEETPAGE �ṹ

    PROPSHEETPAGE psp;

    ZeroMemory(&psp, sizeof(PROPSHEETPAGE));

    psp.dwSize = sizeof(PROPSHEETPAGE);

    psp.dwFlags = PSP_USEREFPARENT | PSP_USETITLE | PSP_DEFAULT;

    psp.hInstance = _AtlBaseModule.GetModuleInstance();

    psp.pszTemplate = MAKEINTRESOURCE(IDD_WMFPROP);

    psp.pszTitle = __TEXT("Ԥ��");

    psp.pfnDlgProc = PropPage_DlgProc;

    psp.lParam = reinterpret_cast<LPARAM>(g_szFile); // Ϊdlgproc��������

    psp.pcRefParent = reinterpret_cast<UINT*>(&g_cnt);

    // ������ҳ��

    HPROPSHEETPAGE hPage = ::CreatePropertySheetPage(&psp);

    // ���ҳ�浽����ҳ

    if(hPage != NULL)

    {

        if(!lpfnAddPage(hPage, lParam))

            ::DestroyPropertySheetPage(hPage);

        return NOERROR;

    }

    return E_INVALIDARG;

}


BOOL CALLBACK PropPage_DlgProc(HWND hwnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)

{

    switch(uiMsg)

    {

    case WM_INITDIALOG:

        HWND hwndMeta = GetDlgItem(hwnd, IDC_METAFILE);
// 
//         LPPROPSHEETPAGE lppsp = reinterpret_cast<LPPROPSHEETPAGE>(lParam);
// 
//         DisplayMetaFile(hwndMeta, reinterpret_cast<LPTSTR>(lppsp->lParam));

        return FALSE;

    }

    return FALSE;

}


