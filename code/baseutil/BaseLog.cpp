

/**************************** 条件编译选项和头文件 ****************************/
#include <iostream>
#include <ctime>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdarg>

#include "BaseLog.h"
#include "RetDefine.h"

#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#endif

/********************************** 宏、常量 **********************************/

#define LOG_OUTPUT_FORMAT			"%s-%5s- [%s]:  %s - [%s(%d)]\n"
#define	LOG_MAX_NUM					100000
#define	LOG_MAX_SIZE 				10240
#define LOG_MAX_TIME_SIZE			24
#define LOG_FILE_MAX_SIZE           (50 * 1024 * 1024)

/********************************** 数据类型 **********************************/

enum E_LogLevel
{
    emLL_Info = 0,
    emLL_Debug,
    emLL_Warn,
    emLL_Error
};

/************************************ 变量 ************************************/

const char* g_MeetLogLevel[] =
{
    "INFO","DEBUG","WARN","ERROR"
};

/************************************ 函数 ************************************/

void GetFmtTimeString(char* );

/*********************************** 类实现 ***********************************/

CBaseLog::CBaseLog()
{
	m_iLogLine = 0;
	m_bPrintf = false;
	m_pComment = new char[LOG_MAX_SIZE];
	memset(m_pComment, 0, LOG_MAX_SIZE);
}

CBaseLog::~CBaseLog()
{
	std::lock_guard<std::mutex> lock(m_cLogMtx);

    if (m_cFileStm.is_open())
    {
		m_cFileStm.close();
    }
	m_cFileStm.clear();
#if defined(WIN32) || defined(WIN64)
	if (m_bPrintf)
	{
		FreeConsole();
	}
#endif
}

uint32_t CBaseLog::LogInit(const char* pFile, bool bPrintf)
{
	// 检查参数
    if (pFile == nullptr)
    {
        return emRC_PARAM_ERR;
    }
    if (m_cFileStm.is_open())
    {
        return emRC_FILE_EXIST_ERR;
    }

	m_szLogFile = pFile;
	m_bPrintf = bPrintf;
   
	m_cFileStm.open(pFile, std::fstream::in | std::fstream::out | std::fstream::app);
	if (!m_cFileStm.is_open()) 
	{
		return emRC_FILE_OPEN_ERR;
	}
#if defined(WIN32) || defined(WIN64)
	if (m_bPrintf)
	{
		::AllocConsole();
	}
#endif
    return emRC_OK;
}

void CBaseLog::LogInfo(const char* pSrcFile, const char* pFunc, int nLine, const char* fmt, ...)
{
    if (!m_cFileStm.is_open())
    {
        return;
    }

	std::lock_guard<std::mutex> lock(m_cLogMtx);

    va_list vl;
    va_start(vl, fmt);
    vsprintf(m_pComment, fmt, vl);
    va_end(vl);

    WriteLog(emLL_Info, pSrcFile, pFunc, nLine);
}

void CBaseLog::LogWarn(const char* pSrcFile, const char* pFunc, int nLine, const char* fmt, ...)
{
	if (!m_cFileStm.is_open())
	{
		return;
	}

	std::lock_guard<std::mutex> lock(m_cLogMtx);

    va_list vl;
    va_start(vl, fmt);
    vsprintf(m_pComment, fmt, vl);
    va_end(vl);

    WriteLog(emLL_Warn, pSrcFile, pFunc, nLine);
}

void CBaseLog::LogEror(const char* pSrcFile, const char* pFunc, int nLine, const char* fmt, ...)
{
	if (!m_cFileStm || !m_cFileStm.is_open())
	{
		return;
	}

	std::lock_guard<std::mutex> lock(m_cLogMtx);

    va_list vl;
    va_start(vl, fmt);
    vsprintf(m_pComment, fmt, vl);
    va_end(vl);

    WriteLog(emLL_Error, pSrcFile, pFunc, nLine);
}

void CBaseLog::CheckLine()
{
    if (m_cFileStm.is_open())
    {
		unsigned int iCurFilePos = m_cFileStm.tellp();
		m_cFileStm.seekp(0, m_cFileStm.end);
		unsigned int iFileSize = m_cFileStm.tellp();
		m_cFileStm.seekp(iCurFilePos, m_cFileStm.beg);
        if (iFileSize >= LOG_FILE_MAX_SIZE)
        {
#if defined(WIN32) || defined(WIN64)
			m_cFileStm.close();
			rename(m_szLogFile.c_str(), std::string(m_szLogFile + ".old").c_str());
			m_iLogLine = 0;
			m_cFileStm.open(m_szLogFile.c_str(), std::fstream::in | std::fstream::out | std::fstream::app);
#else
			assert(false);
#endif
        }
    }
}

void CBaseLog::WriteLog(int iLogLevel, const char* pSrcFile, const char* pFunc, int nLine)
{
    CheckLine();
    if (!m_cFileStm || !m_cFileStm.is_open())
    {
        return;
    }
    m_iLogLine++;

    char szDebugInfo[2048] = { 0 };
    char aNowTime[LOG_MAX_TIME_SIZE] = { 0 };
    char acSrcFile[256] = { 0 };
    strcpy(acSrcFile, pSrcFile);
#if defined(WIN32) || defined(WIN64)
	char* pSrcName = strrchr(acSrcFile, '\\');
#else
	char* pSrcName = strrchr(acSrcFile, '/');
#endif
    if (pSrcName == NULL)
        pSrcName = acSrcFile;
    else
        pSrcName++;

	// 格式化字符串
    GetFmtTimeString(aNowTime);
    if (strlen(m_pComment) > 1900)
    {
		sprintf(szDebugInfo, LOG_OUTPUT_FORMAT, aNowTime, g_MeetLogLevel[iLogLevel], pFunc, "Log Info Length Over Size.", pSrcName, nLine);
    }
    else
    {
		sprintf(szDebugInfo, LOG_OUTPUT_FORMAT, aNowTime, g_MeetLogLevel[iLogLevel], pFunc, m_pComment, pSrcName, nLine);
    }
	// 输出到控制台
    if (m_bPrintf)
    {
#if defined(WIN32) || defined(WIN64)
        DWORD dwRet = 0;
        ::OutputDebugStringA(szDebugInfo);
        ::WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), szDebugInfo, strlen(szDebugInfo), &dwRet, NULL);
#else
		printf(szDebugInfo);
#endif
    }
	// 写到日志文件中
	m_cFileStm << szDebugInfo;
}

void GetFmtTimeString(char* chTimeString)
{
    time_t tt = time(NULL);
    struct tm *pTime = localtime(&tt);
    sprintf(chTimeString, "[%d-%02d-%02d %02d:%02d:%02d]",
            1900 + pTime->tm_year, 1 + pTime->tm_mon, pTime->tm_mday,
            pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
}
