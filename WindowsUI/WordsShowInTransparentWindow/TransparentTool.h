#pragma once



class TransparentTool
{
public:
    TransparentTool(void);
    ~TransparentTool(void);
    static void RemoveBorder(HWND hWnd);
    enum ULW_VALUE
    {
        ULW_V_COLORKEY = ULW_COLORKEY,
        ULW_V_ALPHA = ULW_ALPHA,
    };
    
        //��ULW_ALPHA  �� ��ɫ��λ��Ч  ULW_ALPHA��1����ȫ͸������255����͸������
        //��ULW_COLORKEY  ͸����ֵ��Ч
    static void TransparentAlphaWnd(HWND hWnd, bool drawSomething, 
        ULW_VALUE ulwValue, COLORREF transparentRGB, int alphaDegree); 
    static void InitGDIPlus();
   
private:
    static  HBITMAP CreateDIBBitmap(HDC hdc, int width, int height); 

};

