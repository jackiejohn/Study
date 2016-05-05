
// TestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "afxdialogex.h"
#include <assert.h>
#include <string>
#include "../LogLib/LogLib.h"
#pragma comment(lib, "../Debug/Loglib.lib")

#import "../Debug/WLogger.exe" no_namespace

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg �Ի���



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTestDlg::OnBnClickedButton1()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    ILogger* logger = nullptr;
    HRESULT hr = ::CoCreateInstance(__uuidof(Logger), 0, CLSCTX_LOCAL_SERVER,
                                    __uuidof(ILogger), (void**)&logger);
    assert(SUCCEEDED(hr));
    DWORD err = GetLastError();
    //logger->InitLog();

    std::wstring text = L"hello World";
    BSTR textStr = ::SysAllocString(text.c_str());
    LONG writedLen = logger->Write(&textStr, ::SysStringLen(textStr));
    ::SysFreeString(textStr);

    BSTR bstr(::SysAllocStringByteLen(nullptr, 100));
    LONG readed = 0;
    readed = logger->Read(&bstr, 100);
    ::SysFreeString(bstr);
    logger->Exit();
    logger->Release();

}


void CTestDlg::OnBnClickedButton2()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    FILE* fp = nullptr;
    errno_t err = _tfopen_s(&fp, L"D:\\test\\Unicode.txt", L"w,ccs=UNICODE");
    if (0 != err)
    {
        assert(FALSE);
        return;
    }
    wchar_t buf[5] = L"1234";
    int writted = fwrite(buf, 2, 4, fp);
    fflush(fp);
    fclose(fp);
}


void CTestDlg::OnBnClickedButton3()
{
    // TODO:  �ڴ���ӿؼ�֪ͨ����������
    LogLib log;
    log.Init(L"D:\\test\\atl.log", LOG_INFO_LEVEL_INFO, 100, 1);
    LOG_INFO((L"Hello Log\n"));
    LOG_INFO(L"Hello%d\n", 5);

}
