// UpdateLayeredWindowInMultilayer.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "UpdateLayeredWindowInMultilayer.h"
#include <assert.h>
#include <GdiPlus.h>
#include <WTypes.h>
#include <WindowsX.h>
#include <atlimage.h>
#include <string>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

#pragma comment(lib, "msimg32.lib")

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
	LoadString(hInstance, IDC_UPDATELAYEREDWINDOWINMULTILAYER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_UPDATELAYEREDWINDOWINMULTILAYER));

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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_UPDATELAYEREDWINDOWINMULTILAYER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_UPDATELAYEREDWINDOWINMULTILAYER);
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

void RemoveBorderEx(HWND hWnd)
{
    static bool init = false;
    if (false == init)
    {
        LONG oldStyle = GetWindowLong(hWnd, GWL_STYLE);
        DWORD removeStyle = ~(WS_OVERLAPPED|WS_SYSMENU|WS_MAXIMIZEBOX|
            WS_BORDER|WS_MAXIMIZEBOX|WS_CAPTION|WS_SIZEBOX);
        SetWindowLong(hWnd, GWL_STYLE, oldStyle & removeStyle);
        LONG oldExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
        DWORD removeStyleEx = ~(WS_EX_LEFT|WS_EX_LTRREADING|
            WS_EX_RIGHTSCROLLBAR);
        SetWindowLong(hWnd, GWL_EXSTYLE, oldExStyle & removeStyleEx);
        SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
            SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOMOVE|SWP_NOZORDER|
            SWP_FRAMECHANGED);
        SetMenu(hWnd, NULL);
        init = true;
    }
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



void initGDIP(HWND hWnd)
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    //
    static bool init = false;
    if (!init)
    {
        GdiplusStartupInput gdiplusStartupInput;
        ULONG_PTR           gdiplusToken;

        // Initialize GDI+.
        GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
    }


    //���ַ�ʽ͸���������dc����˸��

    // TransparentWindow(hWnd, true, 200, RGB(0,0,0), 2);

    //  TransparentWindow( this, true, 100, RGB(0,0,0), 2 );

    // TransparentWindow( this, true, i, RGB(0,0,0),3 );


}

RECT ClientToScreen(HWND hWnd, const RECT& rect)
{
    POINT lt = {rect.left, rect.top};
    ClientToScreen(hWnd, &lt);
    POINT rb = {rect.right, rect.bottom};
    ClientToScreen(hWnd, &rb);
    RECT res = {lt.x, lt.y, rb.x, rb.y};
    return res;
}

void DrawTranspareBackground(HWND hWnd, HDC memDC, 
                             int alphaValue)
{
    RECT clientRect;
    ::GetClientRect(hWnd, &clientRect);
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    HDC backDC = CreateCompatibleDC(memDC);
    
    HBITMAP bitmapBMPbk;
    { 
        bitmapBMPbk = CreateDIBCompatibleBitmap(backDC, width, height);
        SelectBitmap(backDC, bitmapBMPbk);  
    }

    HBITMAP bitmapBMP = nullptr;
    {
        bitmapBMP = (HBITMAP)::LoadImageW(
            reinterpret_cast<HINSTANCE>(GetModuleHandle(nullptr)), 
            MAKEINTRESOURCE(IDB_BITMAP1), 
            IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
        if (bitmapBMP == nullptr)
        {
            assert(bitmapBMP);
            return;
        }
    }  

    HBRUSH brush = CreatePatternBrush(bitmapBMP);
    FillRect(backDC, &clientRect, brush);

    HBRUSH slolidBrush = CreateSolidBrush(RGB(0, 255, 0));
    SelectBrush(backDC, slolidBrush);
    Rectangle(backDC, 100, 200, 300, 400);

     BITMAP bitmap;
     GetObject(bitmapBMPbk, sizeof(bitmap), &bitmap);
     for (int h = 0; h < bitmap.bmHeight; ++h)
     {
         for (int w = 0; w < bitmap.bmWidth; ++w)
         {
             int* pixel = (int*)((BYTE*)bitmap.bmBits + 
                 bitmap.bmWidthBytes * h) + w;
             //*pixel |= 0xff000000;
             int a = (GetRValue(*pixel) + GetGValue(*pixel) + 
                 GetBValue(*pixel))/3;
             int r = GetRValue(*pixel) * a/255;
             int g = GetGValue(*pixel) * a/255;
             int b = GetBValue(*pixel) * a/255;
             *pixel = a<<24 | RGB(r, g, b);
         }
     }

    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = alphaValue;
    BOOL ret = ::AlphaBlend(memDC, 0, 0, width, height, backDC, 0, 0, width, 
        height, bfc);
    DWORD err = GetLastError();
    DeleteBrush(brush);
    DeleteBrush(slolidBrush);
    DeleteBitmap(bitmapBMP);
    DeleteBitmap(bitmapBMPbk);
 }

void DrawSolidText(HWND hWnd, HDC memDC)
{

    RECT clientRect;
    ::GetClientRect(hWnd, &clientRect);
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    HDC textDC = CreateCompatibleDC(memDC);
    HBITMAP bitmapBMPbk = CreateDIBCompatibleBitmap(textDC, width, height);
    SelectBitmap(textDC, bitmapBMPbk);

//     {
//         BITMAP bitmap;
//         GetObject(bitmapBMPbk, sizeof(bitmap), &bitmap);
//         //��䱳��
//         for (int i = 0; i < height; ++i)
//         {
//             for (int j = 0; j < width; ++j)
//             {
//                 int* pixel = (int*)((byte*)bitmap.bmBits +
//                     bitmap.bmWidthBytes * i) + j;
//                 *pixel |= 0xff000000 ;
//             }
//         }
//     }

    TCHAR* textShow = L"DrawSolidText ����͸��";
    SetBkMode(textDC, TRANSPARENT);
    SetTextColor(textDC, RGB(255, 0, 0));
    BOOL ret = TextOut(textDC, 500, 300, textShow, _tcslen(textShow));

    {
       BITMAP bitmap;
        GetObject(bitmapBMPbk, sizeof(bitmap), &bitmap);
        for (int h = 0; h < bitmap.bmHeight; ++h)
        {
            for (int w = 0; w < bitmap.bmWidth; ++w)
            {
                int* pixel = (int*)((BYTE*)bitmap.bmBits + 
                    bitmap.bmWidthBytes * h) + w;

                if ((*pixel) & 0x00ffffff)
                {
                    *pixel |= 0xff000000;
//                     int a = (GetRValue(*pixel) + GetGValue(*pixel) + 
//                         GetBValue(*pixel))/3;
//                     int r = GetRValue(*pixel) * a/255;
//                     int g = GetGValue(*pixel) * a/255;
//                     int b = GetBValue(*pixel) * a/255;
//                     *pixel = a<<24 | RGB(r, g, b);
                }
            }
        }
    }

    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = 225;
    ::AlphaBlend(memDC, 0, 0, width, height, textDC, 0, 0, width, height, bfc);

    DeleteBitmap(bitmapBMPbk);
    DeleteDC(textDC);
}

void BackTranspareButTextSolid(HWND hWnd, int alphaValue)
{
    LONG style = GetWindowLong(hWnd, GWL_EXSTYLE);
    if (0 == (WS_EX_LAYERED & style))
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
    }

    HDC hdc = GetDC(hWnd);
    RECT clientRect;
    ::GetClientRect(hWnd, &clientRect);
    RECT wndRect = ClientToScreen(hWnd, clientRect);
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    HDC memDC = CreateCompatibleDC(hdc);
    HBITMAP bitmap = CreateDIBCompatibleBitmap(memDC, width, height);
    SelectBitmap(memDC, bitmap);
    
    //��͸������
    DrawTranspareBackground(hWnd, memDC, alphaValue);
    DrawSolidText(hWnd, memDC);

    POINT dstPt = {wndRect.left, wndRect.top};
    SIZE dstSize = {width, height};
    POINT srcPt = {0, 0};
    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = 255;
    BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, &dstPt, &dstSize, memDC,
        &srcPt, 0, &bfc, ULW_ALPHA);
    DWORD err = GetLastError();
    
    DeleteBitmap(bitmap);
    DeleteDC(memDC);
    ReleaseDC(hWnd, hdc);
}

void DrawTransparePng(HWND hWnd, int alphaValue)
{
    LONG style = GetWindowLong(hWnd, GWL_EXSTYLE);
    if (0 == (WS_EX_LAYERED & style))
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
    }

    HDC hdc = GetDC(hWnd);
    RECT clientRect;

    ::GetClientRect(hWnd, &clientRect); 
    int width = clientRect.right - clientRect.left;
    int height = clientRect.bottom - clientRect.top;

    HDC backDC = CreateCompatibleDC(hdc);   
    HBITMAP bitmapBMPbk;
    { 
        bitmapBMPbk = CreateDIBCompatibleBitmap(backDC, width, height+500);
        SelectBitmap(backDC, bitmapBMPbk);  
    }

    HBITMAP bitmapBMP = nullptr;
    {
        TCHAR fileName[1024] = {0};
        GetModuleFileName(GetModuleHandle(nullptr), fileName,
                          sizeof(fileName)-1);
        std::wstring fileNameStr(fileName);
        size_t pos = 0;
        for (int i = 0; i < 2; ++i)
        {
            pos = fileNameStr.rfind('\\');
            if (pos != fileNameStr.npos)
            {
                fileNameStr.erase(pos);
            }
        }

        if (pos == fileNameStr.npos)
        {
            assert(0 && L"fileNameStr.npos");
            return;
        }

        fileNameStr += L"\\Phone.png";        

        CImage img;
        HRESULT rload = img.Load(fileNameStr.c_str());
        bitmapBMP = img.Detach(); 
        if (bitmapBMP == nullptr)
        {
            assert(bitmapBMP);
            return;
        }

   
        {
            BITMAP bitmap;
            GetObject(bitmapBMP, sizeof(bitmap), &bitmap);
            for (int h = 0; h < bitmap.bmHeight; ++h)
            {
                for (int w = 0; w < bitmap.bmWidth; ++w)
                {
                    int* pixel = (int*)((BYTE*)bitmap.bmBits + 
                        bitmap.bmWidthBytes * h) + w; 
                    int a = (*pixel>>24) & 0xff;
                    int r = GetRValue(*pixel) * a/255;
                    int g = GetGValue(*pixel) * a/255;
                    int b = GetBValue(*pixel) * a/255;
                    *pixel = a<<24 | RGB(r, g, b);
                }
            }
        }

    }
    HBRUSH brush = CreatePatternBrush(bitmapBMP);
    FillRect(backDC, &clientRect, brush);    

    RECT wndRect;
    GetWindowRect(hWnd, &wndRect);
    POINT dstPt = {wndRect.left, wndRect.top};
    SIZE dstSize = {width, height};
    POINT srcPt = {0, 0};
    BLENDFUNCTION bfc = {0};
    bfc.AlphaFormat = AC_SRC_ALPHA;
    bfc.SourceConstantAlpha = alphaValue;
    BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, &dstPt, &dstSize, backDC,
        &srcPt, 0, &bfc, ULW_ALPHA);
    DWORD err = GetLastError();
    DeleteBrush(brush);
    DeleteBitmap(bitmapBMP);
    DeleteBitmap(bitmapBMPbk);
    DeleteDC(backDC);
    ReleaseDC(hWnd, hdc);
}

void GDIDrawTranspareText(HWND hWnd, HDC hdcDevice, HDC hdcMem)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    //ʹ��aphaBlend ʵ��GDIҲ����͸��
    {
        HDC textDC = CreateCompatibleDC(nullptr);
        HBITMAP textBitmap = CreateDIBCompatibleBitmap(hdcDevice, width, height);
        HBITMAP oldTextBitmap = SelectBitmap(textDC, textBitmap);

        LOGFONT logFont = {0};
        logFont.lfCharSet = GB2312_CHARSET;
        _tcscpy_s(logFont.lfFaceName, _T("΢���ź�")); 
        logFont.lfHeight = -80;
        logFont.lfWeight = 40;
        HFONT font = CreateFontIndirect(&logFont);
        if (font == nullptr)
        {
            assert(font);
            return;
        }
        //HFONT oldFont = SelectFont(textDC, font);
        SetBkMode(textDC, TRANSPARENT);
        SetTextColor(textDC, RGB(255, 0, 0));
        TCHAR* text = _T("ʹ��aphaBlend ʵ��GDIҲ����͸��");
        RECT rect = {200, 300, 800, 450};
        int draw = DrawText(textDC, text, _tcslen(text), &rect, DT_CENTER);
        draw = TextOutW(textDC, 100, 400, text, _tcslen(text));
        Ellipse(textDC, 300, 400, 800, 800);
//         SelectFont(textDC, oldFont);
//         DeleteFont(font);

        //��䱳��
         {
            BITMAP bitmap = {0};
            GetObject(textBitmap, sizeof(bitmap), &bitmap);
            for (int i = 0; i < height; ++i)
            {
                for (int j = 0; j < width; ++j)
                {
                    int* pixel = (int*)((BYTE*)bitmap.bmBits + 
                        bitmap.bmWidthBytes * i) + j;

                    if (((*pixel & 0xff000000) != 0xff000000) &&
                        (*pixel & 0xffffffff))
                    {
                        int a = (GetRValue(*pixel) + GetGValue(*pixel) +
                             GetBValue(*pixel))/3;
                         int r = GetRValue(*pixel) * a / 255;
                         int g = GetGValue(*pixel) * a / 255;
                         int b = GetBValue(*pixel) * a / 255;
                     }
                }
            }

            BLENDFUNCTION textBfc = {0};
            textBfc.AlphaFormat = AC_SRC_ALPHA;
            textBfc.SourceConstantAlpha = 255;
            BOOL ret = AlphaBlend(hdcMem, 0, 0, width, height, textDC, 0, 0, width, 
                height, textBfc);
        }
        DeleteBitmap(textBitmap); 
        DeleteDC(textDC);
    }
}

void TransparentWindowUseGDI(HWND hWnd, COLORREF backColor, BYTE alphaValue)
{
    LONG style = GetWindowLong(hWnd, GWL_EXSTYLE);
    if (0 == (WS_EX_LAYERED & style))
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
    }

    HDC hdc = GetDC(hWnd);
    HDC hdcMem = CreateCompatibleDC(hdc);

    RECT rect;
    GetClientRect(hWnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    HBITMAP bitmapMem = CreateDIBCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, bitmapMem);   

    //���ȫͼ����
    {
        BITMAP bitmap;
        GetObject(bitmapMem, sizeof(bitmap), &bitmap);
        for (int i = 0; i < bitmap.bmHeight; ++i)
        {
            for (int j = 0; j < bitmap.bmWidth; ++j)
            {
                int* pixel = (int*)((BYTE*)bitmap.bmBits +
                    bitmap.bmWidthBytes * i) + j;
                *pixel = (0xff000000 | backColor);
            }
        }
    }

    GDIDrawTranspareText(hWnd, hdc, hdcMem);

    RECT rectWin;
    GetWindowRect(hWnd, &rectWin);
    POINT point = {rectWin.left, rectWin.top};
    POINT pointMem = {0, 0};
    SIZE size = {width, height};
    BLENDFUNCTION blend = {0};
    blend.AlphaFormat = 1;
    blend.BlendFlags = 0;
    blend.BlendOp = 0;    
    blend.SourceConstantAlpha = alphaValue;    
    BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, &point, &size, hdcMem, &pointMem, 
        0, &blend, ULW_ALPHA);
    DWORD err = GetLastError();
    if (!ret)
    {      
        assert(0 && L"UpdateLayeredWindow Fail!!!");       
    }
    //DeleteObject(brushTangle);
    DeleteObject(bitmapMem);   
    DeleteDC( hdcMem );
    ReleaseDC(hWnd, hdc);
}


//��LWA_ALPHA  �� ��ɫ��λ��Ч  LWA_ALPHA��1����ȫ͸������255����͸������
//�� LWA_COLORKEY  ͸����ֵ��Ч
void TransparentWindow(HWND hWnd, COLORREF color,
    int transType, int transDegree)
{
    LONG style = GetWindowLong(hWnd, GWL_EXSTYLE);
    if (0 == (WS_EX_LAYERED & style))
    {
        SetWindowLong(hWnd, GWL_EXSTYLE, style | WS_EX_LAYERED);
    }

    HDC hdc = GetDC(hWnd);
    HDC hdcMem = CreateCompatibleDC(hdc);

    RECT rect;
    GetClientRect(hWnd, &rect);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;
    HBITMAP bitmapMem = CreateDIBCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, bitmapMem);   

//     HBRUSH brushTangle = CreateSolidBrush(RGB(0xff, 0, 0));
//     RECT rectangle = {0, 0, 100, 500};
//     Rectangle(hdcMem, 0, 0, 100, 500);
//     FillRect(hdcMem, &rectangle, brushTangle);

    // ���ֻ����� ���ֻ�������⡣GDI �Ķ��� ALPHA ֵΪ0
    TextOut(hdcMem, 200, 200, L"hi WindowUI aaaaaaaaaaaaa !",
        _tcslen( L"hi WindowUI aaaaaaaaaaaaa !"));   

    //GDI+��û����
    Graphics graphics( hdcMem ); 
    Font font(L"΢���ź�", 40.0);
    SolidBrush brush(Color::Yellow);
    graphics.DrawString(L"��ţB��GID+��������", 
        _tcslen(L"��ţB��GID+��������"), &font, PointF(50.0, 50.0), &brush);

    graphics.FillRectangle(&brush,400, 200, 1000, 1000);
    
    RECT rectWin;
    GetWindowRect(hWnd, &rectWin);
    POINT point = {rectWin.left, rectWin.top};
    POINT pointMem = {0, 0};
    SIZE size = {width, height};
    BLENDFUNCTION blend = {0};
    blend.AlphaFormat = 1;
    blend.BlendFlags = 0;
    blend.BlendOp = 0;    
    blend.SourceConstantAlpha = transDegree;    
    BOOL ret = ::UpdateLayeredWindow(hWnd, hdc, &point, &size, hdcMem, &pointMem, 
       color, &blend, transType);
    DWORD err = GetLastError();
    if (!ret)
    {      
        assert(0 && L"UpdateLayeredWindow Fail!!!");       
    }
    //DeleteObject(brushTangle);
    DeleteObject(bitmapMem);   
    DeleteDC( hdcMem );
    ReleaseDC(hWnd, hdc);
}

void OnKeyDown(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RemoveBorderEx(hWnd);
    initGDIP(hWnd);
    //SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE|SWP_NOMOVE);
    switch(wParam)
    {
    case 'A':
        {                   
            TransparentWindow(hWnd, RGB(255, 255, 255), ULW_COLORKEY, 100);
            break;
        }
    case 'B':
        {                   
            TransparentWindow(hWnd, RGB(0, 0, 0), ULW_COLORKEY, 100);
            break;
        }
    case 'C':
        {                                       
            TransparentWindow(hWnd, RGB(255, 255, 255), ULW_OPAQUE, 125);
            break;
        }
    case 'D':
        {                                       
            TransparentWindow(hWnd, RGB(0, 0, 0), ULW_ALPHA, 125);
            break;
        }
    case 'E':
        {                    
            TransparentWindow(hWnd, RGB(255, 255, 255), 
                ULW_ALPHA, 100);
            break;
        }
    case 'F':
        {                    
            TransparentWindow(hWnd, RGB(255, 255, 255), 
                ULW_ALPHA, 0);
            break;
        }
    case 'G':
        {
            TransparentWindowUseGDI(hWnd, RGB(255, 0, 0), 125);
            break;
        }
    case 'H':
        {
            BackTranspareButTextSolid(hWnd, 123);
            break;
        }
    case 'I':
        {
            DrawTransparePng(hWnd, 125);
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
        OutputDebugString(L"WM_PAINT\n");
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
    case WM_KEYDOWN:
        {   
            OnKeyDown(hWnd, message, wParam, lParam);
            break;
        }
    case WM_NCHITTEST:
        {
            return HTCAPTION;
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
