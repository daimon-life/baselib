#if defined(LINUX) || defined(MACOS)

#include "StringUtil.h"
#include "utf.h"

CStringUtil::CStringUtil()
{
}

CStringUtil::~CStringUtil()
{
}

std::string CStringUtil::WCharToChar(const wchar_t *pwszSrc)
{
    std::string szRet;

    char szChar[2048] = { 0 }; 
    WtoUTF8(pwszSrc, -1, szChar, 2048, false);
    szRet = szChar;

    return szRet;
}

std::string CStringUtil::WCharToChar(std::wstring& wszSrc)
{
    return WCharToChar(wszSrc.c_str());
}

std::string CStringUtil::WCharToUTF8(const wchar_t *pwszSrc)
{
    std::string szRet;

    return szRet;
}

std::string CStringUtil::WCharToUTF8(std::wstring& wszSrc)
{
    return WCharToUTF8(wszSrc.c_str());
}

std::wstring CStringUtil::CharToWChar(const char *pszSrc)
{
    std::wstring wszRet;
    
    wchar_t wszChar[2048] = { 0 }; 
    UTF8toW(pszSrc, -1, wszChar, 2048, false);
    wszRet = wszChar;

    return wszRet;
}

std::wstring CStringUtil::CharToWChar(std::string& szSrc)
{
    return CharToWChar(szSrc.c_str());
}

std::wstring CStringUtil::UTF8ToWChar(const char *pszSrc)
{
    std::wstring wszRet;
    
    return wszRet;
}

std::wstring CStringUtil::UTF8ToWChar(std::string& szSrc)
{
    return UTF8ToWChar(szSrc.c_str());
}

#endif // LINUX || MACOS
