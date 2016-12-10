
// C09IconDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "C09IconDraw.h"
#include "C09IconDrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CC09IconDrawDlg �Ի���




CC09IconDrawDlg::CC09IconDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CC09IconDrawDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CC09IconDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CC09IconDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON_EXTRACTICONEX, &CC09IconDrawDlg::OnBnClickedButtonExtracticonex)
    ON_BN_CLICKED(IDC_BUTTON_BrowseForIcon, &CC09IconDrawDlg::OnBnClickedButtonBrowseforicon)
END_MESSAGE_MAP()


// CC09IconDrawDlg ��Ϣ�������

BOOL CC09IconDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CC09IconDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CC09IconDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CC09IconDrawDlg::OnBnClickedButtonExtracticonex()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    HICON bigIcon = nullptr;
    HICON smallIcon = nullptr;
    UINT size = ExtractIconEx(
        L"D:\\Program Files (x86)\\360se\\360se6\\Application\\360se.exe",
        0, &bigIcon, &smallIcon, 5);

    for (UINT i = 0; i < size; ++i)
    {
        DestroyIcon(bigIcon + i);
        DestroyIcon(smallIcon + i);
    }

}

TCHAR g_szFileName[1024] = {0};
HIMAGELIST g_himl = nullptr;
int g_iIconIndex = 0;
HICON g_hIcon = nullptr;

int DoLoadIcons(HWND hDlg, LPTSTR szFileName)
{
    TCHAR szStatus[30] = {0};
    // ȡ��ͼ����
    int iNumOfIcons = reinterpret_cast<int>(ExtractIcon(GetModuleHandle(nullptr),
        szFileName, -1));
    // �����û�����
    HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
    ListView_DeleteAllItems(hwndList);
    wsprintf(szStatus, __TEXT("%d icon(s) found."), iNumOfIcons);
    SetDlgItemText(hDlg, IDC_ICONCOUNT, szStatus);
    // ͬʱ����ͼ���б���б�۲�
    for(int i = 0 ; i < iNumOfIcons ; i++)
    {
        HICON hIcon = ExtractIcon(GetModuleHandle(nullptr), szFileName, i);
        int iIndex = ImageList_AddIcon(g_himl, hIcon);
        // �ӵ����б�۲�
        LV_ITEM lvi;
        ZeroMemory(&lvi, sizeof(LV_ITEM));
        lvi.mask = LVIF_IMAGE | LVIF_TEXT;
        lvi.iItem = iIndex;
        lvi.iImage = iIndex;
        lvi.cchTextMax = 3;
        lvi.pszText = L"ABC";
        ListView_InsertItem(hwndList, &lvi);
    }
    SetWindowText(hwndList, L"ListView!!!");
    return iNumOfIcons;
}
void DoGetIcon(HWND hDlg)
{
    HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
    // ȡ���б�۲��ѡ��������
    g_iIconIndex = -1;
    int i = ListView_GetNextItem(hwndList, -1, LVNI_SELECTED);
    if(i == -1)
        return;
    g_iIconIndex = i;
    // ȡ��ѡ������Ϣ
    LV_ITEM lvi;
    ZeroMemory(&lvi, sizeof(LV_ITEM));
    lvi.mask = LVIF_IMAGE;
    lvi.iItem = i;
    ListView_GetItem(hwndList, &lvi);
    // ȡ��ͼ���ͼ���б��������ͷ���HICON
    g_hIcon = ImageList_GetIcon(g_himl, lvi.iImage, 0);
}


void OnInitDialog(HWND hDlg)
{
    HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
    SetDlgItemText(hDlg, IDC_FILENAME, g_szFileName);
    ListView_SetImageList(hwndList, g_himl, LVSIL_NORMAL);
    DoLoadIcons(hDlg, g_szFileName);
}
void OnBrowse(HWND hDlg)
{
    {
        TCHAR szBuf[1024];
        LVITEM lvi = {0};
       // lvi.mask = LVIF_TEXT;
        lvi.cchTextMax = 1024;
        lvi.pszText = szBuf;
        lvi.iSubItem = 0;
        HWND hwndList = GetDlgItem(hDlg, IDC_LIST1);
        int len = (int)SendMessage(hwndList, LVM_GETITEMTEXT, (WPARAM)0, (LPARAM)&lvi);
        DWORD err = GetLastError();       

    }
    TCHAR szWinDir[MAX_PATH] = {0};
    TCHAR szFile[MAX_PATH] = {0};
    // ����ļ�...
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(OPENFILENAME));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = __TEXT("Icons/0*.exe;*.dll;*.ico/0");
    ofn.nMaxFile = MAX_PATH;
    GetWindowsDirectory(szWinDir, MAX_PATH);
    ofn.lpstrInitialDir = szWinDir;
    ofn.lpstrFile = szFile;
    if(!GetOpenFileName(&ofn))
        return;
    SetDlgItemText(hDlg, IDC_FILENAME, ofn.lpstrFile);
    DoLoadIcons(hDlg, ofn.lpstrFile);
    lstrcpy(g_szFileName, ofn.lpstrFile);
}

BOOL CALLBACK BrowseIconProc(HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uiMsg)
    {
    case WM_INITDIALOG:
        OnInitDialog(hDlg);
        break;
    case WM_COMMAND:
        switch(wParam)
        {
        case IDC_BROWSE:
            OnBrowse(hDlg);
            break;
        case IDCANCEL:
            EndDialog(hDlg, FALSE);
            return FALSE;
        case IDOK:
            DoGetIcon(hDlg);
            EndDialog(hDlg, TRUE);
            return FALSE;
        }
    }
    return FALSE;
}

int SHBrowseForIcon(LPTSTR szFile, HICON* lphIcon)
{
    // ��������ͼ���Ĭ�ϳߴ�(ͨ����32 x 32)
    int cx = GetSystemMetrics(SM_CXICON);
    int cy = GetSystemMetrics(SM_CYICON);
    lstrcpy(g_szFileName, szFile);
    g_himl = ImageList_Create(cx, cy, ILC_MASK, 1, 1);
    DialogBox(GetModuleHandle(nullptr),MAKEINTRESOURCE(IDD_BROWSEICON),
        GetFocus(),BrowseIconProc);
    // �ͷ�ͼ���б�
    ImageList_Destroy(g_himl);
    // ���÷���ֵ(�ļ������Ѿ��ı�)
    *lphIcon = g_hIcon;
    lstrcpy(szFile, g_szFileName);
    // ��������ɶԻ����������
    return g_iIconIndex;
}

void CC09IconDrawDlg::OnBnClickedButtonBrowseforicon()
{
    HICON icon = nullptr;
    SHBrowseForIcon(
        L"D:\\Program Files (x86)\\360se\\360se6\\Application\\360se.exe",
        &icon);
}
