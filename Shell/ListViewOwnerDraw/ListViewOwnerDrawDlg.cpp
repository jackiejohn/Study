
// ListViewOwnerDrawDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListViewOwnerDraw.h"
#include "ListViewOwnerDrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListViewOwnerDrawDlg �Ի���




CListViewOwnerDrawDlg::CListViewOwnerDrawDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CListViewOwnerDrawDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListViewOwnerDrawDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CListViewOwnerDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST1, &CListViewOwnerDrawDlg::OnLvnGetdispinfoList1)
END_MESSAGE_MAP()


// CListViewOwnerDrawDlg ��Ϣ�������

BOOL CListViewOwnerDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
    m_listCtrl.SetItemCount(200);
    m_listCtrl.SetWindowTextW(L"CListViewOwnerDrawDlgListView");
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CListViewOwnerDrawDlg::OnPaint()
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
HCURSOR CListViewOwnerDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CListViewOwnerDrawDlg::OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
    LV_ITEM* pItem= &(pDispInfo)->item;

    int iItemIndx= pItem->iItem; 
    TCHAR szBuf[10] = L"A:";
    szBuf[2] = L'A' + iItemIndx;
    if (pItem->mask & LVIF_TEXT)
    {
        switch(pItem->iSubItem)
        {
        case 0:
            {
                memcpy(pItem->pszText, szBuf, 4*sizeof(TCHAR));
            }
            break;
        case 1:
            {
                memcpy(pItem->pszText, szBuf, 4*sizeof(TCHAR));
            }
            break;
        }
    }

    *pResult = 0;
}
