// HolleWorld.h : CHolleWorld ������

#pragma once
#include "resource.h"       // ������



#include "TestA_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;


// CHolleWorld

class ATL_NO_VTABLE CHolleWorld :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CHolleWorld, &CLSID_HolleWorld>,
	public IDispatchImpl<IHolleWorld, &IID_IHolleWorld, &LIBID_TestALib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CHolleWorld()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_HOLLEWORLD)


BEGIN_COM_MAP(CHolleWorld)
	COM_INTERFACE_ENTRY(IHolleWorld)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:



};

OBJECT_ENTRY_AUTO(__uuidof(HolleWorld), CHolleWorld)
