// BlurGlass.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "BlurGlass.h"
#include <GdiPlus.h>
#include <dwmapi.h>
#include <WindowsX.h>

using namespace Gdiplus;
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "gdiplus.lib")

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

    //GDI+
    ULONG_PTR token;
    GdiplusStartupInput input;
    GdiplusStartup(&token, &input, nullptr);

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BLURGLASS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BLURGLASS));

	// ����Ϣѭ��:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

    GdiplusShutdown(token);
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BLURGLASS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BLURGLASS);
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



HBITMAP  CreateDIBCompatibleBitmap(HDC hdc, int nWidth, int nHeight )
{   
    BYTE* pBits;
    BITMAPINFOHEADER          bmih;    
    ZeroMemory( &bmih, sizeof( BITMAPINFOHEADER ) );   

    bmih.biSize                 = sizeof( BITMAPINFOHEADER );    
    bmih.biWidth                = nWidth;
    bmih.biHeight               = nHeight;
    bmih.biPlanes               = 1 ;    
    bmih.biBitCount             = 32;//����һ��Ҫ��32    
    bmih.biCompression          = BI_RGB ;    
    bmih.biSizeImage            = 0 ;    
    bmih.biXPelsPerMeter        = 0 ;    
    bmih.biYPelsPerMeter        = 0 ;    
    bmih.biClrUsed              = 0 ;    
    bmih.biClrImportant         = 0 ;   
    HBITMAP hBitMap = CreateDIBSection( hdc, ( BITMAPINFO * )&bmih,  DIB_RGB_COLORS, ( VOID** )&pBits, NULL, 0 );   
    return hBitMap;   
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
    case WM_CREATE:
        {
            SetWindowPos(hWnd, HWND_TOP, 500, 300, 800, 300, SWP_SHOWWINDOW);
            LONG style = GetWindowLong(hWnd, GWL_STYLE);
            SetWindowLong(hWnd, GWL_STYLE, 
                style &
                ~(WS_BORDER|WS_MAXIMIZEBOX|WS_MINIMIZEBOX|WS_SIZEBOX|
                WS_SYSMENU|WS_CAPTION|WS_OVERLAPPED));
            LONG oldExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            DWORD removeStyleEx = ~(WS_EX_LEFT|WS_EX_LTRREADING|
                WS_EX_RIGHTSCROLLBAR);
            SetWindowLong(hWnd, GWL_EXSTYLE, oldExStyle & removeStyleEx);
            SetMenu(hWnd, nullptr);

//             DWM_BLURBEHIND bb = {0};
//             bb.dwFlags = DWM_BB_ENABLE;
//             bb.fEnable = TRUE;
//             bb.hRgnBlur = nullptr;
//             DwmEnableBlurBehindWindow(hWnd, &bb);

            break;
        }
	case WM_PAINT:
        {
            hdc = BeginPaint(hWnd, &ps); 
            RECT rcClient;
            GetClientRect(hWnd, &rcClient);
            int width = rcClient.right - rcClient.left;
            int height = rcClient.bottom - rcClient.top;

            LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
            if ((exStyle & WS_EX_LAYERED))
            {
       

                HDC comDC = CreateCompatibleDC(hdc);
                HBITMAP bitmap = CreateDIBCompatibleBitmap(comDC, width, height);
                SelectBitmap(comDC, bitmap);
                Graphics graph(comDC);
                //����ͻ�����
  
    //             BOOL comEnabel(FALSE);
    //             DwmIsCompositionEnabled(&comEnabel);
    //             SolidBrush br(comEnabel? Color::Black : Color::DarkGray);
    //             graph.FillRectangle(&br, rcClient.left, rcClient.top,
    //                 rcClient.right, rcClient.bottom);

                SolidBrush brush(Color::Blue);
                graph.FillRectangle(&brush, 20, 20, 80, 80);

                RECT winRect;
                GetWindowRect(hWnd, &winRect);
                POINT dstPt = {winRect.left, winRect.top};
                SIZE dstSize = {width, height};
                POINT srcPt = {0, 0};
                BLENDFUNCTION bfc = {0};
                bfc.AlphaFormat = AC_SRC_ALPHA;
                bfc.SourceConstantAlpha = 240;
                BOOL ret = UpdateLayeredWindow(hWnd, hdc, &dstPt, &dstSize, 
                    comDC, &srcPt, 0, &bfc, ULW_ALPHA);

                DeleteBitmap(bitmap);
                DeleteDC(comDC);
            }
            else
            {   
                HDC comDC = CreateCompatibleDC(hdc);
                HBITMAP bitmap = CreateDIBCompatibleBitmap(comDC, width, height);
                HBITMAP oldBitmap = SelectBitmap(comDC, bitmap);

                RECT rcClient;
                GetClientRect(hWnd, &rcClient);
                Graphics graph(comDC);
                BOOL comEnabel(FALSE);
                DwmIsCompositionEnabled(&comEnabel);
                SolidBrush br(comEnabel? Color::Black : Color::DarkGray);
                graph.FillRectangle(&br, rcClient.left, rcClient.top,
                    rcClient.right, rcClient.bottom);

                BitBlt(hdc, 0, 0, width, height, comDC, 0, 0, SRCCOPY);
                SelectBitmap(comDC, oldBitmap);
                DeleteBitmap(bitmap);
                DeleteDC(comDC);

            }

            EndPaint(hWnd, &ps);
            break;
        }
    case WM_KEYDOWN:
        {
            switch(wParam)
            {
            case 'A':
                {
                    SetWindowPos(hWnd, HWND_TOPMOST, 1000, 350, 600,
                        50, SWP_NOZORDER);
                    SetWindowPos(hWnd, HWND_TOPMOST, 300, 100, 50,
                        600, SWP_NOZORDER);

                    SendMessage(hWnd, WM_PAINT, 0, 0);
                    break;
                }
            case 'B':
                {
                    SetWindowPos(hWnd, HWND_TOPMOST, 350, 300, 50, 
                        600, SWP_NOZORDER);
                    SetWindowPos(hWnd, HWND_TOPMOST, 700, 700, 600, 
                        50, SWP_NOZORDER);
                    SendMessage(hWnd, WM_PAINT, 0, 0);
                    break;
                }
            case 'C':
                {
                    DWM_BLURBEHIND bb = {0};
                    bb.dwFlags = DWM_BB_ENABLE/* |DWM_BB_BLURREGION*/;
                    bb.fEnable = TRUE;
                    //HRGN rgn = CreateRectRgn(0, 0, 100, 50);
                    //bb.hRgnBlur = rgn;
                    DwmEnableBlurBehindWindow(hWnd, &bb);
                   // DeleteObject(rgn);


                    //Layer Window
                    {
                        LONG exStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
                        if ((exStyle & WS_EX_LAYERED) == 0)
                        {
                            SetWindowLong(hWnd, GWL_EXSTYLE, exStyle | WS_EX_LAYERED);
                        }       
                    }
                    SendMessage(hWnd, WM_PAINT, 0, 0);
                    SetWindowRgn(hWnd, nullptr, TRUE);


                    break;
                }
            }
            break;
        }
    case WM_NCHITTEST:
        {
            return HTCAPTION;
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
