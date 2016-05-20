#pragma once
//#pragma warning( push  )
#pragma warning( disable:4996 )
#include <stdio.h>
#include <stdarg.h>

#define MAX_LOG_FILE_SIZE    5   // Ĭ�������־�ļ�5M

#define LOG_TRACE(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Trace X; } while (0);

#define LOG_DEBUG(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Debug X; } while (0);

#define LOG_INFO(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Info X; } while (0);

#define LOG_WARN(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Warn X; } while (0);

#define LOG_ERROR(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Error X; } while (0);

#define LOG_FATAL(X) do { \
    CLog::Instance()->SetSourceFileName(__FILE__); \
    CLog::Instance()->SetLine(__LINE__); \
    CLog::Instance()->SetFunctionName(__FUNCTION__); \
    CLog::Instance()->Fatal X; } while (0);

class CLog
{
public:
    enum
    {
        LEVEL_TRACE   = 0,      // TRACE
        LEVEL_DEBUG,            // DEBUG
        LEVEL_INFO,             // INFO
        LEVEL_WARN,             // WARN
        LEVEL_ERROR,            // ERROR
        LEVEL_FATAL,            // FATAL
        LEVEL_UNKNWN            // UNKNWN
    };

    enum
    {
        ARCHIVAL = 0,           // �鵵��־ģʽ
        CIRCULAR                // ѭ����־ģʽ
    };

public:
    CLog();
    ~CLog();
    static CLog *  Instance();

public:
    int     Init(const char *pPath, int nLevel = CLog::LEVEL_INFO, 
        int nMaxLogFileSize = MAX_LOG_FILE_SIZE, int nMode = CLog::CIRCULAR, int nFileCount = 2);
    void    SetMaxLogFileSize(int nSize);
    void    SetLevel(int nLevel);
    void    SetMode(int nMode);
    void    SetFileCount(int nFileCount);
    void    SetLine(int nLine);
    void    SetSourceFileName(const char *pFileName);
    void    SetFunctionName(const char *pFuncName);
    void    Trace(const char *fmt, ...);
    void    Debug(const char *fmt, ...);
    void    Info(const char *fmt, ...);
    void    Warn(const char *fmt, ...);
    void    Error(const char *fmt, ...);
    void    Fatal(const char *fmt, ...);

private:
    void    Log(int nLevel, const char *fmt, va_list p);

private:
    int     m_nLevel;           // ��־����
    int     m_nMaxLogFileSize;  // �����־�ļ�
    int     m_nMode;            // ��־ģʽ��ARCHIVAL����CIRCULAR
    int     m_nFileCount;       // ��־�ļ�������ѭ����־�������壩
    int     m_nLine;            // ����
    char *  m_pSrcFileName;     // Դ�ļ���
    char *  m_pFuncName;        // ������
    char *  m_pPath;            // ��ǰ��־�ļ�·��
    FILE *  m_pLogFile;         // ��ǰ��־�ļ�FILEָ��
};
//#pragma warning( pop )