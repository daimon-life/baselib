#pragma once

#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_


#include <string>

// 
class CStringUtil
{
public:
    static std::wstring CharToWChar(const char *pszSrc);
    static std::wstring CharToWChar(const std::string& szSrc);
    static std::wstring UTF8ToWChar(const char* pszSrc);
    static std::wstring UTF8ToWChar(const std::string& szSrc);
    static std::string  WCharToChar(const wchar_t *pwszSrc);
    static std::string  WCharToChar(const std::wstring& wszSrc);
    static std::string  WCharToUTF8(const wchar_t *pwszSrc);
    static std::string  WCharToUTF8(const std::wstring& wszSrc);

    CStringUtil() = delete;
    ~CStringUtil() = delete;
};

#endif // _STRING_UTIL_H_
