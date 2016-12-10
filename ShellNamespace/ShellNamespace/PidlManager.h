#ifndef __PIDL_MANAGER_H__
#define __PIDL_MANAGER_H__
class CPidlManager
{
public:
    typedef enum _enum_item_type
    {
        FOLDER,
        FILE,
    }ITEM_TYPE;

    typedef enum _enum_item_state
    {
        LOCATE,         //���������ļ�(�ǲ�����״̬)
        CONFLICT,       //�ļ��г�ͻ
        REMOTE,         //Զ��
        COMITING,       //�ϴ���
        DOWNLOADING,    //������
        PAUSEDOWNLOAD,  //��ͣ����
        PAUSECOMIT,     //��ͣ�ϴ�
    }ITEM_STATE;

    typedef struct _tag_pidl_data
    {
        ITEM_TYPE  type;
        ITEM_STATE state;
        DWORD dwLength;
        TCHAR szName[1]; //Name\0RealPath\0
    }PIDLDATA, FAR* LPPIDLDATA;

public:
    LPITEMIDLIST Create( ITEM_TYPE type, const TCHAR* pszName\
        , const TCHAR* pszRealName, ITEM_STATE state = LOCATE  );
    LPITEMIDLIST GetNextItem( LPITEMIDLIST lpIDL );
    UINT         CountItem( LPITEMIDLIST lpIDL );
    void         Delete(LPITEMIDLIST pidl);
    LPITEMIDLIST GetLastItem(LPCITEMIDLIST pidl);
    UINT         GetByteSize(LPCITEMIDLIST pidl);
    bool         IsSingle(LPCITEMIDLIST pidl);
    LPITEMIDLIST Concatenate(LPCITEMIDLIST, LPCITEMIDLIST);
    LPITEMIDLIST Copy(LPCITEMIDLIST pidlSrc);
    const TCHAR* GetItemName(LPCITEMIDLIST);
    ITEM_TYPE    GetItemType(LPCITEMIDLIST pidl);
    ITEM_STATE   GetItemState( LPCITEMIDLIST pidl );
    HRESULT      GetFullName(LPCITEMIDLIST pidl,LPTSTR szFullName,DWORD *pdwLen); 
    const TCHAR* GetRealPath( LPCITEMIDLIST pidl ); 
    bool         HasSubFolder(LPCITEMIDLIST pidl); 
    bool         ReplaceRoot( TCHAR* pszDir );
    const TCHAR* GetRootDir();
    bool         IsValidDir(LPCTSTR lpszDir);

private:
    LPPIDLDATA   GetDataPointer( const LPCITEMIDLIST lpIDL );
    //ȡidl����ʵ����
    DWORD        GetPidlDataLen( const LPPIDLDATA lpPidl );
    //ȡ�ڵ�����
    const TCHAR* GetPidlDataName( const LPPIDLDATA lpPidl );
    //ȡ��ʵ�ڵ�·��
    const TCHAR* GetPidlDataRealPath( const LPPIDLDATA lpPidl );

};
#endif