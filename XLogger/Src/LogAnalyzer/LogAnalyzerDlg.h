// LogAnalyzerDlg.h : ͷ�ļ�
//

#pragma once

#include "Data.h"
#include "afxwin.h"

// CLogAnalyzerDlg �Ի���
class CLogAnalyzerDlg : public CDialog
{
// ����
public:
	CLogAnalyzerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CData m_oLogData;	
	CRect m_rcDlgRect;
	CRect m_rcEditRect;

	void EnableAnalyzer(BOOL bEnable);
	void SetDlgTitle(CString FileName = _T(""));

// �Ի�������
	enum { IDD = IDD_LOGANALYZER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonOpenfile();
	afx_msg void OnBnClickedButtonNotreturn();
	afx_msg void OnBnClickedButtonLongtime();
	CEdit m_edtResult;
	afx_msg void OnBnClickedButtonRelation();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButtonCpu();
	afx_msg void OnBnClickedButtonTimes();
};
