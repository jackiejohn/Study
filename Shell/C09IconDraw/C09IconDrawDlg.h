
// C09IconDrawDlg.h : ͷ�ļ�
//

#pragma once


// CC09IconDrawDlg �Ի���
class CC09IconDrawDlg : public CDialogEx
{
// ����
public:
	CC09IconDrawDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_C09ICONDRAW_DIALOG };

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
    afx_msg void OnBnClickedButtonExtracticonex();
    afx_msg void OnBnClickedButtonBrowseforicon();
};
