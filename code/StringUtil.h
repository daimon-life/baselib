#pragma once


#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_


#include <string>


class CStringUtil
{
public:
    CStringUtil();
    ~CStringUtil();

public:
    static std::string  WCharToChar(const wchar_t *pwszSrc);
    static std::string  WCharToChar(std::wstring& wszSrc);
    static std::string  WCharToUTF8(const wchar_t *pwszSrc);
    static std::string  WCharToUTF8(std::wstring& wszSrc);
    static std::wstring CharToWChar(const char *pszSrc);
    static std::wstring CharToWChar(std::string& szSrc);
    static std::wstring UTF8ToWChar(const char *pszSrc);
    static std::wstring UTF8ToWChar(std::string& szSrc);
};


#endif // _STRING_UTIL_H_
