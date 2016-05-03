// Logger.h : CLogger ������

#pragma once
#include "resource.h"       // ������

#include <memory>

#include "WLogger_i.h"



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE ƽ̨(�粻�ṩ��ȫ DCOM ֧�ֵ� Windows Mobile ƽ̨)���޷���ȷ֧�ֵ��߳� COM ���󡣶��� _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ��ǿ�� ATL ֧�ִ������߳� COM ����ʵ�ֲ�����ʹ���䵥�߳� COM ����ʵ�֡�rgs �ļ��е��߳�ģ���ѱ�����Ϊ��Free����ԭ���Ǹ�ģ���Ƿ� DCOM Windows CE ƽ̨֧�ֵ�Ψһ�߳�ģ�͡�"
#endif

using namespace ATL;

class ShareMem;


// CLogger

class ATL_NO_VTABLE CLogger :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CLogger, &CLSID_Logger>,
	public IDispatchImpl<ILogger, &IID_ILogger, &LIBID_WLoggerLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
    CLogger();
    ~CLogger();

DECLARE_REGISTRY_RESOURCEID(IDR_LOGGER)


BEGIN_COM_MAP(CLogger)
	COM_INTERFACE_ENTRY(ILogger)
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

    STDMETHOD(Init)();
    STDMETHOD(Exit)();
    STDMETHOD(Write)(BSTR* writeStr, LONG wantWriteLen, LONG* writedLen);

private:
    std::unique_ptr<ShareMem> shareMem_;

};

OBJECT_ENTRY_AUTO(__uuidof(Logger), CLogger)
