
// HScrollBarDlg.h : ͷ�ļ�
//

#pragma once


// CHScrollBarDlg �Ի���
class CHScrollBarDlg : public CDialogEx
{
// ����
public:
	CHScrollBarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HSCROLLBAR_DIALOG };

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
};
