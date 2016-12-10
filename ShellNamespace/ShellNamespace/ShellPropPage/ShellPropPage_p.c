

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Wed Aug 24 18:14:29 2016
 */
/* Compiler settings for ShellPropPage.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "ShellPropPage_i.h"

#define TYPE_FORMAT_STRING_SIZE   3                                 
#define PROC_FORMAT_STRING_SIZE   1                                 
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _ShellPropPage_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ShellPropPage_MIDL_TYPE_FORMAT_STRING;

typedef struct _ShellPropPage_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ShellPropPage_MIDL_PROC_FORMAT_STRING;

typedef struct _ShellPropPage_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ShellPropPage_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const ShellPropPage_MIDL_TYPE_FORMAT_STRING ShellPropPage__MIDL_TypeFormatString;
extern const ShellPropPage_MIDL_PROC_FORMAT_STRING ShellPropPage__MIDL_ProcFormatString;
extern const ShellPropPage_MIDL_EXPR_FORMAT_STRING ShellPropPage__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IPropPage_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IPropPage_ProxyInfo;



#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const ShellPropPage_MIDL_PROC_FORMAT_STRING ShellPropPage__MIDL_ProcFormatString =
    {
        0,
        {

			0x0
        }
    };

static const ShellPropPage_MIDL_TYPE_FORMAT_STRING ShellPropPage__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IPropPage, ver. 0.0,
   GUID={0xA126E108,0xCB26,0x49F6,{0x86,0x95,0x66,0xAF,0x76,0x1E,0x05,0xFF}} */

#pragma code_seg(".orpc")
static const unsigned short IPropPage_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IPropPage_ProxyInfo =
    {
    &Object_StubDesc,
    ShellPropPage__MIDL_ProcFormatString.Format,
    &IPropPage_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IPropPage_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ShellPropPage__MIDL_ProcFormatString.Format,
    &IPropPage_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _IPropPageProxyVtbl = 
{
    0,
    &IID_IPropPage,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION IPropPage_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _IPropPageStubVtbl =
{
    &IID_IPropPage,
    &IPropPage_ServerInfo,
    7,
    &IPropPage_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    ShellPropPage__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _ShellPropPage_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPropPageProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ShellPropPage_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPropPageStubVtbl,
    0
};

PCInterfaceName const _ShellPropPage_InterfaceNamesList[] = 
{
    "IPropPage",
    0
};

const IID *  const _ShellPropPage_BaseIIDList[] = 
{
    &IID_IDispatch,
    0
};


#define _ShellPropPage_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ShellPropPage, pIID, n)

int __stdcall _ShellPropPage_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_ShellPropPage_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo ShellPropPage_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ShellPropPage_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ShellPropPage_StubVtblList,
    (const PCInterfaceName * ) & _ShellPropPage_InterfaceNamesList,
    (const IID ** ) & _ShellPropPage_BaseIIDList,
    & _ShellPropPage_IID_Lookup, 
    1,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

