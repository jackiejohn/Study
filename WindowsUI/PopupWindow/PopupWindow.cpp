// PopupWindow.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "PopupWindow.h"
#include <assert.h>
#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

#define WM_CREATE_POPUP_WINDOW WM_USER+100

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
	LoadString(hInstance, IDC_POPUPWINDOW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_POPUPWINDOW));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_POPUPWINDOW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_POPUPWINDOW);
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


LRESULT CALLBACK GrandsonProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    return DefWindowProc(hWnd, message, wParam, lParam);
}



LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
    case WM_PAINT:
        {
            HDC dc = GetDC(hWnd);
            RECT rect;
            GetClientRect(hWnd, &rect);
            HBRUSH brush = (HBRUSH)CreateSolidBrush(RGB(0, 100, 0));
            FillRect(dc, &rect, brush);
            DeleteObject(brush);
            ReleaseDC(hWnd, dc);
            break;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case 'B'://������popup window
                {
                    WNDCLASSEX wcs = {0};
                    wcs.cbSize = sizeof(wcs);
                    HBRUSH hbr = CreateSolidBrush(RGB(150, 125, 250));
                    wcs.hbrBackground = hbr;
                    wcs.hInstance = hInst;
                    wcs.lpfnWndProc = GrandsonProc;
                    wcs.lpszClassName = L"GrandsonProcPopup";
                    wcs.style = CS_VREDRAW | CS_HREDRAW;
                    ATOM at = RegisterClassEx(&wcs);
                    assert(at != 0 && L"at != 0");

                    HWND hChild = CreateWindowExW(0, wcs.lpszClassName, wcs.lpszClassName,
                        WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW, 200, 200, 500, 300, hWnd, NULL, hInst, NULL);
    
                    break;
                }
            case 'C'://�������̵�popupwindow
                {
                    HWND anotherWindow = FindWindow(NULL,
                        L"PopupWIndowAnotherProcess");
                    if (anotherWindow)
                    {
//                          SendMessage(anotherWindow, WM_CREATE_POPUP_WINDOW, 
//                              (WPARAM)hWnd, 0);
                       // anotherWindow = (HWND)((int)anotherWindow - 1);
                        WCHAR szBufA[1024];
                        _stprintf(szBufA, L"GetTickCount = %d   IsWindow(anotherWindow) = %d\n", GetTickCount(), (IsWindow(anotherWindow)));
                        OutputDebugString(szBufA);
                         SendMessageTimeout(anotherWindow, WM_CREATE_POPUP_WINDOW, (WPARAM)hWnd, 0, SMTO_BLOCK, 1000, NULL);
                         WCHAR szBuf[1024];
                         _stprintf(szBuf, L"GetTickCount = %d   IsWindow(anotherWindow) = %d\n", GetTickCount(), IsWindow(anotherWindow));
                         OutputDebugString(szBuf);
                    }
                    else
                    {
                        assert(0 &&
                            L"FindWindow(NULL, L\"PopupWindowAnotherProcessWindow\"); Fail!");
                    }
                    break;
                }
            }

            break;
        }
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
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
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case 'A':
                {
                    WNDCLASSEX wcs = {0};
                    wcs.cbSize = sizeof(wcs);
                    //HBRUSH hbr = CreateSolidBrush(RGB(0, 125, 0));
                    //wcs.hbrBackground = hbr;
                    wcs.hInstance = hInst;
                    wcs.lpfnWndProc = ChildProc;
                    wcs.lpszClassName = L"ChildWindowPopup";
                    wcs.style = CS_VREDRAW | CS_HREDRAW;
                    ATOM at = RegisterClassEx(&wcs);
                    assert(at != 0 && L"at != 0");

                    HWND hChild = CreateWindowExW(0, wcs.lpszClassName, wcs.lpszClassName,
                        WS_BORDER|WS_VISIBLE|WS_OVERLAPPEDWINDOW, 100, 200, 1000, 800, NULL, NULL, hInst, NULL);
                    break;
                }  
            case 'B'://������popup window
                {
                    WNDCLASSEX wcs = {0};
                    wcs.cbSize = sizeof(wcs);
                    HBRUSH hbr = CreateSolidBrush(RGB(150, 125, 250));
                    wcs.hbrBackground = hbr;
                    wcs.hInstance = hInst;
                    wcs.lpfnWndProc = GrandsonProc;
                    wcs.lpszClassName = L"GrandsonProcPopup";
                    wcs.style = CS_VREDRAW | CS_HREDRAW;
                    RegisterClassEx(&wcs);

                    HWND hChild = CreateWindowExW(0, wcs.lpszClassName, wcs.lpszClassName,
                        WS_CHILD|WS_VISIBLE|WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN, 200, 200, 500, 300, hWnd, NULL, hInst, NULL);

                    break;
                }
            }            
            break;
        }
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
