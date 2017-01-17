// Win7TaskBar.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win7TaskBar.h"
#include <ShlObj.h>
#include <dwmapi.h>

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
	LoadString(hInstance, IDC_WIN7TASKBAR, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN7TASKBAR));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN7TASKBAR));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN7TASKBAR);
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


int WM_TASKBARBUTTONCREATED = 0;
ITaskbarList4* g_taskBar = nullptr;
enum TBUTTON
{
    TBUTTON_LEFT,
    TBUTTON_MIDDLE,
    TBUTTON_RIGHT,
};

void OnThumbnailClicked(int wmId)
{
    switch(wmId)
    {
    case TBUTTON_LEFT:
        {
            OutputDebugString(L"TBUTTON_LEFT\n");
            break;
        }
    case TBUTTON_MIDDLE:
        {
            OutputDebugString(L"TBUTTON_MIDDLE\n");
            break;
        }
    case TBUTTON_RIGHT:
        {
            OutputDebugString(L"TBUTTON_RIGHT\n");
            break;
        }
    }
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

    if (message == WM_TASKBARBUTTONCREATED)
    {
        ::CoCreateInstance(CLSID_TaskbarList, nullptr, CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&g_taskBar));
        if (g_taskBar)
        {
            g_taskBar->HrInit();
        }
        return 0;
    }

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
        if (wmEvent == THBN_CLICKED)
        {
            OnThumbnailClicked(wmId);
            return 0;
        }
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
    case WM_CREATE:
        {
            WM_TASKBARBUTTONCREATED = 
                ::RegisterWindowMessage(L"TaskbarButtonCreated");
            break;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case 'A':
                {
//                     HICON icon = reinterpret_cast<HICON>(
//                         LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), 
//                         IMAGE_ICON, 0, 0, LR_SHARED));
                    HICON icon = reinterpret_cast<HICON>(
                        LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
                    g_taskBar->SetProgressState(hWnd, TBPF_PAUSED);
                    g_taskBar->SetProgressValue(hWnd, 50, 100);
                    g_taskBar->SetOverlayIcon(hWnd, icon, L"TestIcon");
                    break;
                }
            case 'B':
                {
                    THUMBBUTTONMASK mask = THB_ICON|THB_TOOLTIP;
                    THUMBBUTTON buttons[3];
                    {
                        buttons[0].dwMask = mask;
                        buttons[0].iId = TBUTTON_LEFT;
                        HICON icon = reinterpret_cast<HICON>(
                            LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_LEFT), 
                            IMAGE_ICON, 32, 32, LR_SHARED));
                        buttons[0].hIcon = icon;
//                         buttons[0].hIcon = LoadIcon(
//                             hInst, MAKEINTRESOURCE(IDI_ICON_LEFT));
        
                        _tcscpy_s(buttons[0].szTip, L"Left");
                    }
         
                    {
                        buttons[1].dwMask = mask;
                        buttons[1].iId = TBUTTON_MIDDLE;
                        HICON icon = reinterpret_cast<HICON>(
                            LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_MIDDLE), 
                            IMAGE_ICON, 128, 128, LR_SHARED));
                        buttons[1].hIcon = icon;
//                         buttons[1].hIcon = LoadIcon(
//                             hInst, MAKEINTRESOURCE(IDI_ICON_MIDDLE));
                        _tcscpy_s(buttons[1].szTip, L"Middle");
                    }
                    {
                        buttons[2].dwMask = mask;
                        buttons[2].iId = TBUTTON_RIGHT;
                        HICON icon = reinterpret_cast<HICON>(
                            LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON_RIGHT), 
                            IMAGE_ICON, 128, 128, LR_SHARED));
                        buttons[2].hIcon = icon;
//                         buttons[2].hIcon = LoadIcon(
//                             hInst, MAKEINTRESOURCE(IDI_ICON_RIGHT));
                        _tcscpy_s(buttons[2].szTip, L"Right");
                    }
                    g_taskBar->ThumbBarAddButtons(hWnd, _countof(buttons), 
                        buttons);
                    break;
                }
            case 'C':
                {
                    g_taskBar->SetThumbnailTooltip(hWnd, L"Hello Taskbar");
                    break;
                }
            case 'D':
                {
                    BOOL enable = TRUE;
                    DwmSetWindowAttribute(hWnd, DWMWA_HAS_ICONIC_BITMAP,
                        &enable, sizeof(enable));
                    DwmSetWindowAttribute(hWnd, DWMWA_FORCE_ICONIC_REPRESENTATION,
                        &enable, sizeof(enable));

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
