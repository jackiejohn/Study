#include "stdafx.h"
#include "LogFile.h"
#include <assert.h>
#include "../LogLib/LogLibRef.h"


LogFile::LogFile()
    : isInit_(false)
    , fp_(nullptr, [](FILE* p){ fclose(p); })
    , logPath_()
    , fileSize_(LogFileSize)
    , fileCount_(LogFileCount)
{
}


LogFile::~LogFile()
{
}

void LogFile::Init(const TCHAR* logPath, LOG_INFO_LEVEL level,
                  int fileSize, int fileCount)
{
    logPath_ = logPath;
    fileSize_ = fileSize;
    fileCount_ = fileCount;
    isInit_ = true;

    FILE* fp = nullptr;
    errno_t err = _tfopen_s(&fp, logPath_.c_str(), _T("a, ccs=UNICODE"));
    if (0 != err)
    {
        assert(0);
        return;
    }
    fp_.reset(fp);
}

void LogFile::Exit()
{
    fp_.reset();
}

bool LogFile::WriteToFile(const TCHAR* text, int len, int* writted)
{
    if (!isInit_)
    {
        return false;
    }
    if (len == 0)
    {
        *writted = 0;
        return true;
    }
    *writted = fwrite(text, sizeof(TCHAR), len, fp_.get());
    std::wstring textdub(text, len);
    OutputDebugString(textdub.c_str());
    if (*writted <= 0)
    {
        return false;
    }
    fflush(fp_.get());
    return true;
}
