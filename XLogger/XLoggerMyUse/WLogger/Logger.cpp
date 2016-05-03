// Logger.cpp : CLogger ��ʵ��

#include "stdafx.h"
#include "Logger.h"
#pragma comment(lib, "../Debug/ShareMem.lib")
#include "../ShareMem/ShareMem.h"


// CLogger
CLogger::CLogger()
    :shareMem_(new ShareMem())
{
}

CLogger::~CLogger()
{
}


STDMETHODIMP CLogger::Init()
{
    // TODO:  �ڴ����ʵ�ִ���
    shareMem_->Init();
    return S_OK;
}


STDMETHODIMP CLogger::Exit()
{
    // TODO:  �ڴ����ʵ�ִ���
    shareMem_->TryExit();
    shareMem_->Exit();
    return S_OK;
}



STDMETHODIMP CLogger::Write(BSTR* writeStr, LONG wantWriteLen, LONG* writedLen)
{
    CComBSTR bstr(*writeStr);
    TCHAR* szBuf = bstr;
    shareMem_->Write(szBuf, wantWriteLen, reinterpret_cast<int*>(writedLen));
    return S_OK;
}



