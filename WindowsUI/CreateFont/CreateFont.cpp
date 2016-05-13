// CreateFont.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CreateFont.h"
#include <string>
#include <sstream>
#include <WindowsX.h>
#include <assert.h>

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

std::wstring g_text = L"һ����Ϸһ���Σ��Ҳ����¡�";
std::wstring g_fontName = L"΢���ź�";
int g_fontSize = 72;
bool g_fontDirectHori = false;

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_CREATEFONT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CREATEFONT));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CREATEFONT));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_CREATEFONT);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


int FontSizeToPixel(HDC hDC, int fontSize)
{
    return -GetDeviceCaps(hDC, LOGPIXELSY)*fontSize/72;
}
//
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
    bool fresh = false;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
        case 1000:
            {
                if (wmEvent == EN_UPDATE)
                {
                    HWND editHwnd = GetDlgItem(hWnd, 1000);
                    TCHAR szBuf[1024];
                    GetWindowText(editHwnd, szBuf, 
                        sizeof(szBuf)/sizeof(szBuf[0])-1);
                    if (_tcslen(szBuf) > 0)
                    {
                        g_text = szBuf;
                    }
                    fresh = true;
                }
                break;
            }
        case ID_FONTNAME_YAHEI:
            {
                g_fontName = L"΢���ź�";
                fresh = true;
                break;
            }
        case ID_FONTNAME_SONGTI:
            {
                g_fontName = L"����";
                fresh = true;
                break;
            }
        case ID_FONTNAME_BLACK:
            {
                g_fontName = L"����";
                fresh = true;
                break;
            }
        case ID_FONTNAME_HUAWENCAIYUN:
            {
                g_fontName = L"���Ĳ���";
                fresh = true;
                break;
            }
        case ID_FONTNAME_JITI:
            {
                g_fontName = L"����";
                fresh = true;
                break;
            }
        case ID_FONTSIZE_36:
            {
                g_fontSize = 36;
                fresh = true;
                break;
            }
        case ID_FONTSIZE_72:
            {
                g_fontSize = 72;
                fresh = true;
                break;
            }
        case ID_DIRECT_HORI:
            {
                g_fontDirectHori = true;
                fresh = true;
                break;
            }
        case ID_DIRECT_VERT:
            {
                g_fontDirectHori = false;
                fresh = true;
                break;
            }
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
        if (fresh)
        {
            RECT rect;
            GetClientRect(hWnd, &rect);
            InvalidateRect(hWnd, &rect, TRUE);
        }
		break;
	case WM_PAINT:        
        {
            hdc = BeginPaint(hWnd, &ps);

            {
                TCHAR szTip[100] = L"�����룺 ";
                BOOL ret = ::TextOut(hdc, 400, 30, szTip, _tcslen(szTip));
            }

            // TODO: �ڴ���������ͼ����...
            {
                LOGFONT logFont = {0};
                std::wstring fontName = g_fontName;
                if (!g_fontDirectHori)
                {
                    fontName = L"@" + g_fontName;
                }
                _tcscpy_s(logFont.lfFaceName, 32-1, fontName.c_str());
                logFont.lfCharSet = GB2312_CHARSET;
                logFont.lfHeight = FontSizeToPixel(hdc, g_fontSize);
                logFont.lfEscapement = g_fontDirectHori ? 0 : 2700;
                logFont.lfOrientation = logFont.lfEscapement;
                if (logFont.lfWeight > 610 && !wcscmp(L"@΢���ź�", logFont.lfFaceName))
                {
                    logFont.lfWeight = 610;
                }
                HFONT newFont = CreateFontIndirect(&logFont);
                HFONT oldFont = SelectFont(hdc, newFont);

                RECT rect = {50, 50, 1200, 200};
                BOOL ret = ::TextOut(hdc, 200, 100, g_text.c_str(), g_text.length());
                SelectFont(hdc, oldFont);
                DeleteFont(newFont);
            }

            {
                LOGFONT logFont = {0};
                std::wstring fontName = g_fontName;
                if (!g_fontDirectHori)
                {
                    fontName = L"@" + g_fontName;
                }
                _tcscpy_s(logFont.lfFaceName, 32-1, fontName.c_str());
                logFont.lfCharSet = GB2312_CHARSET;
                logFont.lfHeight = FontSizeToPixel(hdc, 20);
                HFONT newFont = CreateFontIndirect(&logFont);
                HFONT oldFont = SelectFont(hdc, newFont);

                {
                    SIZE allSize = {0};
                    ::GetTextExtentPoint32W(
                        hdc, g_text.c_str(), g_text.length(), &allSize);
                    std::wstringstream allString;
                    allString << L"�ܳ���:" << allSize.cx << L", " << allSize.cy;
                    BOOL ret = ::TextOut(hdc, 100, 0,
                        allString.str().c_str(), allString.str().length());
                }

                {
                    int perx = 300;
                    for (UINT i = 0; i < g_text.size(); ++i)
                    {
                        SIZE perSize = {0};
                        std::wstring perString(1, g_text[i]);
                        BOOL ret = ::TextOut(hdc, perx, 400, 
                            perString.c_str(), perString.length());

                        {
                            ::GetTextExtentPoint32W(
                                hdc, perString.c_str(), 1, &perSize);
                            std::wstringstream allString;
                            allString << perSize.cx
                                << L", " << perSize.cy;
                            BOOL retPer = ::TextOut(hdc, perx, 500, 
                                allString.str().c_str(), allString.str().length());
                        }

                        perx += 150;
                    }

                }
                SelectFont(hdc, oldFont);
                DeleteFont(newFont);
            }

   

            EndPaint(hWnd, &ps);
            break;
        }
    case WM_CREATE:
        {
            ShowWindow(hWnd, SW_SHOWMAXIMIZED);
            HWND editHwnd = CreateWindow(L"EDIT", L"", 
                WS_VISIBLE|WS_BORDER|WS_CHILD, 
                400, 50, 500, 50, hWnd, (HMENU)1000, hInst, 0);
            assert(editHwnd);
            break;
        }
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
