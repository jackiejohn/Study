// Test.cpp : ����Ӧ�ó������ڵ㡣
//




{


#include "stdafx.h"
#include "Win32Project12.h"


#define MAX_LOADSTRING 100
#define IDC_OKBTN 200


    // ȫ�ֱ���: 
    HINSTANCE hInst; // ��ǰʵ��
    TCHAR szTitle[MAX_LOADSTRING]; // �������ı�
    TCHAR szWindowClass[MAX_LOADSTRING]; // ����������


    // �˴���ģ���а����ĺ�����ǰ������: 
    ATOM MyRegisterClass(HINSTANCE hInstance);
    BOOL InitInstance(HINSTANCE, int);
    LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
    INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
    HWND hOkBtn = NULL;
    LRESULT CALLBACK StaticWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {

        switch (msg)
        {
        case WM_CREATE:
            {
                hOkBtn = CreateWindowEx(0, L"Button", L"TEST", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                    10, 20, 102, 30, hWnd, (HMENU) 111, (HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE)/* GetModuleHandle(NULL)*/, NULL);


                hOkBtn = CreateWindowEx(0, L"Button", L"TEST", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                    112, 20, 102, 30, hWnd, (HMENU) 111, (HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE)/* GetModuleHandle(NULL)*/, NULL);

            }
            break;
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }


    BOOL RegB()
    {


        WNDCLASSEX wc;
        ZeroMemory(&wc, sizeof(wc));
        wc.cbSize = sizeof(wc);
        wc.lpszClassName = L"gggg";
        wc.lpfnWndProc = StaticWndProc;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.cbWndExtra = 0;
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;// CS_HREDRAW;// CS_GLOBALCLASS/*|CS_SAVEBITS*/;
        return RegisterClassEx(&wc);
    }




    int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
        _In_opt_ HINSTANCE hPrevInstance,
        _In_ LPTSTR    lpCmdLine,
        _In_ int       nCmdShow)
    {
        UNREFERENCED_PARAMETER(hPrevInstance);
        UNREFERENCED_PARAMETER(lpCmdLine);


        // TODO:  �ڴ˷��ô��롣
        MSG msg;
        HACCEL hAccelTable;


        // ��ʼ��ȫ���ַ���
        LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
        LoadString(hInstance, IDC_WIN32PROJECT12, szWindowClass, MAX_LOADSTRING);
        MyRegisterClass(hInstance);


        RegB();
        // ִ��Ӧ�ó����ʼ��: 
        if (!InitInstance(hInstance, nCmdShow))
        {
            return FALSE;
        }


        hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT12));


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
    //  ����:  MyRegisterClass()
    //
    //  Ŀ��:  ע�ᴰ���ࡣ
    //
    ATOM MyRegisterClass(HINSTANCE hInstance)
    {
        WNDCLASSEX wcex;


        wcex.cbSize = sizeof(WNDCLASSEX);


        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32PROJECT12));
        wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCE(IDC_WIN32PROJECT12);
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


        return RegisterClassEx(&wcex);
    }


    //
    //   ����:  InitInstance(HINSTANCE, int)
    //
    //   Ŀ��:  ����ʵ�����������������
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
    //  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
    //
    //  Ŀ��:    ���������ڵ���Ϣ��
    //
    //  WM_COMMAND - ����Ӧ�ó���˵�
    //  WM_PAINT - ����������
    //  WM_DESTROY - �����˳���Ϣ������
    //
    //




    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        int wmId, wmEvent;
        PAINTSTRUCT ps;
        HDC hdc;


        switch (message)
        {
        case WM_INITDIALOG:


            break;


        case WM_COMMAND:
            OutputDebugString(L"CCCCC");
            wmId = LOWORD(wParam);
            wmEvent = HIWORD(wParam);
            // �����˵�ѡ��: 
            switch (wmId)
            {
            case IDM_ABOUT:
                OutputDebugString(L"TTTT");
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                OutputDebugString(L"DDDD");
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
            // TODO:  �ڴ���������ͼ����...
            EndPaint(hWnd, &ps);
            break;
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
        TCHAR * search;
        RECT rect = { 0 };
        GetClientRect(hDlg, &rect);
        HWND hOkBtn = NULL;
        switch (message)
        {
        case WM_INITDIALOG:


            CreateWindowEx(0, L"Button", L"button_��¼.png", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                101, 201, 102, 30, hDlg, (HMENU) 111, GetModuleHandle(NULL), NULL);


            // SetWindowLongPtr(hOkBtn, GWL_WNDPROC, (LONG_PTR) DlgLoginBtnPro);
            // SetWindowLongPtr(hOkBtn, GWL_USERDATA, (LONG_PTR) ChangeOkBtnStatus);
            // SendMessage(hOkBtn, WM_SETFOCUS, 0, 0);


            return (INT_PTR) TRUE;


        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK)
            {
                search = L"E:\\c++\\Test\\2013\\Win32Project12\\Win32Project12\\LoginForm\\*.png";
                WIN32_FIND_DATA fdd;
                HANDLE AFind = FindFirstFile(search, &fdd);
                TCHAR * s = NULL;
                if (AFind != INVALID_HANDLE_VALUE)
                    do
                    {
                        s = fdd.cFileName;
                        int i;
                        //if (!(fdd..dwFileAttributes && FILE_ATTRIBUTE_DIRECTORY)) && valid_library_name(ffd.cFileName))
                    } while (FindNextFile(AFind, &fdd));
                    MessageBox(NULL, s, L"aa", 0);
                    FindClose(AFind);
                    //EndDialog(hDlg, LOWORD(wParam));
                    return (INT_PTR) TRUE;
            }
            if (LOWORD(wParam) == IDCANCEL)
            {
                EndDialog(hDlg, LOWORD(wParam));
                return (INT_PTR) TRUE;
            }
            break;
        }
        return (INT_PTR) FALSE;
    }
}
#include "stdafx.h"
#include "Test.h"

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
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
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
