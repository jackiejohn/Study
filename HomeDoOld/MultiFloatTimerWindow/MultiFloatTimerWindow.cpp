// MultiFloatTimerWindow.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MultiFloatTimerWindow.h"
#include "MultiWnd.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
 	MSG msg;
 	HACCEL hAccelTable;
 	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MULTIFLOATTIMERWINDOW));

    MultiWnd wnd;
    wnd.Show();

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


