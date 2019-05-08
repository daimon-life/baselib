#ifdef WIN32

#include "StringUtil.h"
#include <assert.h>
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>


CStringUtil::CStringUtil()
{
}

CStringUtil::~CStringUtil()
{
}

std::string CStringUtil::WCharToChar(const wchar_t *pwszSrc)
{
    std::string szRet;
    int nCharLen = 0;
    char *pChar = NULL;

    do
    {
        assert(pwszSrc);
        if (pwszSrc == NULL)
            break;

        nCharLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
        if (nCharLen == 0)
            break;

        pChar = (char *)malloc(nCharLen + 1);
        if (pChar == NULL)
            break;

        memset(pChar, 0, nCharLen + 1);
        nCharLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pChar, nCharLen, NULL, NULL);
        if (nCharLen == 0)
        {
            assert(nCharLen);
        }
    } while (false);
    if (nCharLen > 0)
    {
        szRet.assign(pChar);
    }
    if (pChar)
    {
        free(pChar);
    }
    return szRet;
}

std::string CStringUtil::WCharToChar(std::wstring& wszSrc)
{
    return WCharToChar(wszSrc.c_str());
}

std::string CStringUtil::WCharToUTF8(const wchar_t *pwszSrc)
{
    std::string szRet;
    int nCharLen = 0;
    char *pChar = NULL;

    do
    {
        assert(pwszSrc);
        if (pwszSrc == NULL)
            break;

        nCharLen = WideCharToMultiByte(CP_UTF8, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
        if (nCharLen == 0)
            break;

        pChar = (char *)malloc(nCharLen + 1);
        if (pChar == NULL)
            break;

        memset(pChar, 0, nCharLen + 1);
        nCharLen = WideCharToMultiByte(CP_UTF8, 0, pwszSrc, -1, pChar, nCharLen, NULL, NULL);
        if (nCharLen == 0)
        {
            assert(nCharLen);
        }
    } while (false);
    if (nCharLen > 0)
    {
        szRet.assign(pChar);
    }
    if (pChar)
    {
        free(pChar);
    }
    return szRet;
}

std::string CStringUtil::WCharToUTF8(std::wstring& wszSrc)
{
    return WCharToUTF8(wszSrc.c_str());
}

std::wstring CStringUtil::CharToWChar(const char *pszSrc)
{
    std::wstring wszRet;
    int nWCharLen = 0;
    wchar_t *pWChar = NULL;

    do
    {
        assert(pszSrc);
        if (pszSrc == NULL)
            break;

        nWCharLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
        if (nWCharLen == 0)
            break;

        pWChar = (wchar_t *)malloc((nWCharLen + 1) * sizeof(wchar_t));
        if (pWChar == NULL)
            break;

        memset(pWChar, 0, (nWCharLen + 1) * sizeof(wchar_t));
        nWCharLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pWChar, nWCharLen);
        if (nWCharLen == 0)
        {
            assert(nWCharLen);
        }
    } while (false);
    if (nWCharLen > 0)
    {
        wszRet.assign(pWChar);
    }
    if (pWChar)
    {
        free(pWChar);
    }
    return wszRet;
}

std::wstring CStringUtil::CharToWChar(std::string& szSrc)
{
    return CharToWChar(szSrc.c_str());
}

std::wstring CStringUtil::UTF8ToWChar(const char *pszSrc)
{
    std::wstring wszRet;
    int nWCharLen = 0;
    wchar_t *pWChar = NULL;

    do
    {
        assert(pszSrc);
        if (pszSrc == NULL)
            break;

        nWCharLen = MultiByteToWideChar(CP_UTF8, 0, pszSrc, -1, NULL, 0);
        if (nWCharLen == 0)
            break;

        pWChar = (wchar_t *)malloc((nWCharLen + 1) * sizeof(wchar_t));
        if (pWChar == NULL)
            break;

        memset(pWChar, 0, (nWCharLen + 1) * sizeof(wchar_t));
        nWCharLen = MultiByteToWideChar(CP_UTF8, 0, pszSrc, -1, pWChar, nWCharLen);
        if (nWCharLen == 0)
        {
            assert(nWCharLen);
        }
    } while (false);
    if (nWCharLen > 0)
    {
        wszRet.assign(pWChar);
    }
    if (pWChar)
    {
        free(pWChar);
    }
    return wszRet;
}

std::wstring CStringUtil::UTF8ToWChar(std::string& szSrc)
{
    return UTF8ToWChar(szSrc.c_str());
}

#endif // WIN32
