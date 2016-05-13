#include "StdAfx.h"
#include <sstream>
#include "WDateWnd.h"


WDateWnd::WDateWnd(void)
{

}


WDateWnd::~WDateWnd(void)
{
}


bool WDateWnd::ProcessMessage( UINT msg, WPARAM wParam,
    LPARAM lParam, LRESULT* result )
{

    switch (msg)
    {
    case WM_CREATE:
        {
            SetTimer(hWnd_, 1000, 500, nullptr);
            break;
        }
    case WM_TIMER:
        {
            SYSTEMTIME time;
            GetLocalTime(&time);
            std::wstringstream ss;
            ss  <<time.wYear<<L"��"
                <<time.wMonth<<L"��"
                <<time.wDay<<L"��";

            SetWindowText(ss.str());
            InvalidateRect();
            break;
        }
    }
    return __super::ProcessMessage(msg, wParam, lParam, result);
}