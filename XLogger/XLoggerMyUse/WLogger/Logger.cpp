// Logger.cpp : CLogger ��ʵ��

#include "stdafx.h"
#include "Logger.h"
#include "LoggerImple.h"


// CLogger
CLogger::CLogger()
    : impl_(new LoggerImple())
{
}

CLogger::~CLogger()
{
}


STDMETHODIMP CLogger::Exit()
{
    impl_->Exit();
    return S_OK;
}

STDMETHODIMP CLogger::InitLog(BSTR logPath, LONG level, 
                              LONG fileSize, LONG fileCount)
{
    // TODO:  �ڴ�����ʵ�ִ���
    impl_->InitLog(logPath, level, fileSize, fileCount);
    return S_OK;
}


STDMETHODIMP CLogger::log(BSTR text, LONG len, LONG* logged)
{
    // TODO:  �ڴ�����ʵ�ִ���
    return impl_->log(text, len, logged);
}