
// ListViewOwnerDrawDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CListViewOwnerDrawDlg �Ի���
class CListViewOwnerDrawDlg : public CDialogEx
{
// ����
public:
	CListViewOwnerDrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_LISTVIEWOWNERDRAW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CListCtrl m_listCtrl;
    afx_msg void OnLvnGetdispinfoList1(NMHDR *pNMHDR, LRESULT *pResult);
};
