// win32Demo.cpp : ����Ӧ�ó������ڵ㡣
//
 
#include "stdafx.h"
#include "DlgSet.h"
static TCHAR szRootPath[MAX_PATH] = {0};
LRESULT CALLBACK SetProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
        {
            SetDlgItemText( hDlg, IDC_EDIT_DIRINPUT, szRootPath );
            SetFocus( GetDlgItem( hDlg, IDC_EDIT_DIRINPUT ) );
		    return TRUE;
        }
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL
            || IDC_BUTTON_EXECUTE == LOWORD(wParam) ) 
		{
            INT_PTR id = IDCANCEL;
            if ( LOWORD(wParam) == IDC_BUTTON_EXECUTE )
            {
                TCHAR szPath[MAX_PATH] = {0};
                if( GetDlgItemText( hDlg, IDC_EDIT_DIRINPUT, szPath, MAX_PATH ) > 0 )
                {
                    int nLast = (int)_tcslen(szPath)-1;
                    if( szPath[nLast] == _T('\\')
                        || szPath[nLast] == _T('/') )
                    {
                        szPath[nLast] = 0;
                    }
                    WIN32_FIND_DATA FindFileData;  
                    HANDLE hFind=::FindFirstFile(szPath,&FindFileData);  
                    if(INVALID_HANDLE_VALUE == hFind)
                    {
                        MessageBox( NULL, _T("��������ȷ��·��"), _T("����"), MB_OK | MB_ICONERROR );
                        SetFocus( GetDlgItem( hDlg, IDC_EDIT_DIRINPUT ) );
                        return TRUE;  
                    }
                    if ( !(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
                    {
                        MessageBox( NULL, _T("��������ȷ��·��"), _T("����"), MB_OK | MB_ICONERROR );
                        SetFocus( GetDlgItem( hDlg, IDC_EDIT_DIRINPUT ) );
                        return TRUE;
                    }
                    FindClose(hFind); 
                    szPath[nLast+1] = _T('\\');
                    for ( int _i = 0; _i < nLast; ++_i )
                    {
                        if ( szPath[_i] == _T('/'))
                        {
                            szPath[_i] = _T('\\');
                        }
                    }
                    if ( _tcslen(szPath) == _tcslen(szRootPath)
                        || _tcsncicmp( szPath, szRootPath, _tcslen(szPath) ) )
                    {
                        CopyMemory( szRootPath, szPath, MAX_PATH* sizeof(TCHAR) );
                        id = IDOK;
                    }
                }
                else
                {
                    MessageBox( NULL, _T("��������ȷ��·��"), _T("����"), MB_OK | MB_ICONERROR );
                    SetFocus( GetDlgItem( hDlg, IDC_EDIT_DIRINPUT ) );
                    return TRUE;
                }
            }
			EndDialog(hDlg, LOWORD(id));
			return TRUE;
		}
        else if ( IDC_BUTTON_BROWSE == LOWORD(wParam) )
        {
            BROWSEINFO   bi;       
            ITEMIDLIST*   pidl;
            TCHAR szPath[MAX_PATH] = {0};
            RtlSecureZeroMemory(&bi, sizeof(bi));/*�������ṹ��0����Ȼ��һ������Ա���*/
            bi.lpszTitle =   TEXT("��ѡ��һ���ļ���:");//��ʾ�ı���
            bi.ulFlags   =   BIF_RETURNONLYFSDIRS;
            pidl = SHBrowseForFolder(&bi); //�����ļ���������ڣ���ѡȡĿ¼
            if (pidl)  
            {       
                SHGetPathFromIDList(pidl, szPath ); /*���ˣ�û����Ļ�ѡ����ļ���·���Ѿ�������folderPath��*/
                SetDlgItemText( hDlg, IDC_EDIT_DIRINPUT, szPath );
            }
        }
		break;
	}
	return FALSE;
}

const TCHAR* DialogBoxReRoot( HWND hParent, const TCHAR* szInit )
{
    if ( szInit )
    {
        CopyMemory( szRootPath, szInit, (_tcslen(szInit)+1)* sizeof(TCHAR) );
    }
    if( IDOK == DialogBox(_Module.GetResourceInstance(), (LPCTSTR)IDD_DIALOG_SET, hParent, (DLGPROC)SetProc) )
    {
        return szRootPath;
    }
    return NULL;
}