// MiniRestoreMax.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MiniRestoreMax.h"

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
	LoadString(hInstance, IDC_MINIRESTOREMAX, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MINIRESTOREMAX));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINIRESTOREMAX));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_MINIRESTOREMAX);
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

#define TIMER_CHANGE_SIZE 100
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
    case WM_TIMER:
        {
            switch(wParam)
            {
            case TIMER_CHANGE_SIZE:
                {
                    const UINT cCommonFlags = SWP_NOACTIVATE | SWP_NOCOPYBITS | 
                        SWP_NOOWNERZORDER | SWP_NOZORDER;
                    if (::IsWindow(hWnd))
                    {  
                        RECT rcNew = {100, 200, 900, 400};
                        ::SetWindowPos(hWnd, nullptr, rcNew.left, rcNew.top, rcNew.right - rcNew.left, rcNew.bottom - rcNew.top, cCommonFlags);
                        if (::IsIconic(hWnd) || ::IsZoomed(hWnd))
                        {

                            WINDOWPLACEMENT wp = {};
                            wp.length = sizeof(wp);
                            ::GetWindowPlacement(hWnd, &wp);
                            wp.rcNormalPosition = rcNew;
                            wp.flags = WPF_ASYNCWINDOWPLACEMENT;
                            wp.showCmd = ::IsIconic(hWnd) ? SC_MINIMIZE : SC_RESTORE;
                            ::SetWindowPlacement(hWnd, &wp);
                             ::ShowWindow(hWnd, wp.flags);
                           
                        }
                    }
                    OutputDebugString(L"TIMER_CHANGE_SIZE\n");
//                     SetWindowLong(hWnd, GWL_STYLE, 
//                         GetWindowLong(hWnd, GWL_STYLE) | WS_MAXIMIZEBOX);
                    KillTimer(hWnd, wParam);
                    break;
                }
            }
            break;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case 'A':
                {
                    MoveWindow(hWnd, 10, 10, 200, 100, TRUE);
                    break;
                }
            }
            break;
        }
    case WM_SYSCOMMAND:
        {
            if (wParam == SC_MINIMIZE || wParam == SC_RESTORE || wParam == SC_MAXIMIZE)
            {       
                switch (wParam)
                {
                case SC_RESTORE:                 
                    RECT mainWnd;
                    GetWindowRect(hWnd, &mainWnd);
                    OutputDebugString(L"WM_SYSCOMMAND   SC_RESTORE\n ");                    
                    break;
                case SC_MINIMIZE:
                    SetTimer(hWnd, TIMER_CHANGE_SIZE, 1000, NULL);   
                    break;  
                }
            }
            return DefWindowProc(hWnd, message, wParam, lParam);
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
