#pragma once

#ifndef _BASE_LOG_SIMPLE_H_
#define _BASE_LOG_SIMPLE_H_

#include <string>
#include <fstream>
#include <mutex>


// simple base log class
class CBaseLogSimple
{
public:
	CBaseLogSimple();
	~CBaseLogSimple();
	// 
	uint32_t LogInit(const char* pFile,bool bPrint);
	void     LogInfo(const char* pSrcFile,const char* pFunc,int iLine,const char* fmt,...);
	void     LogWarn(const char* pSrcFile,const char* pFunc,int iLine,const char* fmt,...);	 
	void     LogEror(const char* pSrcFile,const char* pFunc,int iLine,const char* fmt,...);
		
protected:
	void WriteLog(int iLogLevel, const char* pSrcFile, const char* pFunc, int iLine);
	void CheckLine();					

private:
	int	                                        m_iLogLine;					// 日志文件已写行数	
	bool	                                    m_bPrintf;					// 输出日志时是否printf	
	std::string                                 m_szLogFile;                // 日志文件全路径	
	std::fstream                                m_cFileStm;                 // 日志文件流	
    std::mutex                                  m_cLogMtx;                  // 日志锁	
	char*				                        m_pComment;					// 日志输出内容
};


extern CBaseLogSimple* g_pSimpleLog;

#define    LOG_INIT					g_pSimpleLog->LogInit
#if defined(WIN32) || defined(WIN64)	
#define    LOG_INFO(...) 			g_pSimpleLog->LogInfo(__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#define    LOG_WARN(...) 			g_pSimpleLog->LogWarn(__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#define    LOG_EROR(...) 			g_pSimpleLog->LogEror(__FILE__,__FUNCTION__,__LINE__,##__VA_ARGS__)
#else
#define    LOG_INFO(args...) 		g_pSimpleLog->LogInfo(__FILE__,__func__,__LINE__,##args)
#define    LOG_WARN(args...) 		g_pSimpleLog->LogWarn(__FILE__,__func__,__LINE__,##args)
#define    LOG_EROR(args...) 		g_pSimpleLog->LogEror(__FILE__,__func__,__LINE__,##args)
#endif


#endif // _BASE_LOG_SIMPLE_H_
