#pragma once
#include <atlbase.h>
#include "LogLibRef.h"
struct ILogger;
class ConnectionCom : public LogLibObserver
{
public:
    ConnectionCom();
    ~ConnectionCom();
    virtual void Init(const TCHAR* logPath, LOG_INFO_LEVEL level,
              int fileSize, int fileCount) override;
    virtual void Exit() override;

    virtual bool log(const TCHAR* text, int len, int* logged) override;


private:
    CComPtr<ILogger> logger_;

};

