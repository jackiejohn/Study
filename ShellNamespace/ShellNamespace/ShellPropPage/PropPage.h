// PropPage.h : CPropPage ������

#pragma once
#include "resource.h"       // ������
#include <CommCtrl.h>
#pragma comment(lib, "comctl32.lib")

#include "IShellExtInitImpl.h" // IShellExtInit

#include "IShellPropSheetExtImpl.h" // IShellPropSheetExt

BOOL CALLBACK PropPage_DlgProc(HWND, UINT, WPARAM, LPARAM);

#include "ShellPropPage_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CPropPage

class ATL_NO_VTABLE CPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPropPage, &CLSID_PropPage>,
    public IShellExtInitImpl,
    public IShellPropSheetExtImpl,
	public IDispatchImpl<IPropPage, &IID_IPropPage, &LIBID_ShellPropPageLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CPropPage()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_PROPPAGE)


BEGIN_COM_MAP(CPropPage)
	COM_INTERFACE_ENTRY(IPropPage)
	COM_INTERFACE_ENTRY(IDispatch)
    COM_INTERFACE_ENTRY(IShellExtInit)

    COM_INTERFACE_ENTRY(IShellPropSheetExt)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

    // IPropPage

public:

    STDMETHOD(Initialize)(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

    STDMETHOD(AddPages)(LPFNADDPROPSHEETPAGE, LPARAM);


};

OBJECT_ENTRY_AUTO(__uuidof(PropPage), CPropPage)
