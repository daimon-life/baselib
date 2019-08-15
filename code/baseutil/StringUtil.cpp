#include <cassert>
#include <cstdint>
#include "StringUtil.h"

#if defined(WIN32) || defined(WIN64)
#include <Windows.h>
#pragma warning(disable:4333)
#endif

/* macro of break free */
#ifndef CHECK_BREAK
#define CHECK_BREAK(bIsBreak)           if ((bIsBreak)) { break; }
#endif
#ifndef SAFE_FREE
#define SAFE_FREE(p)                    { if (p) { free((p)); (p)= NULL; } }
#endif

uint32_t UTF8ToUnicode_LittleEndian(const char* , wchar_t*);
uint32_t UnicodeToUTF8_LittleEndian(const wchar_t* , char*);

std::wstring CStringUtil::CharToWChar(const char *pszSrc)
{
	std::wstring wszRet;

#if defined(WIN32) || defined(WIN64)
	int iWCharLen = 0;
	wchar_t *pWChar = nullptr;
	do
	{
		assert(pszSrc);
		CHECK_BREAK(pszSrc == nullptr);
		iWCharLen = ::MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
		CHECK_BREAK(iWCharLen == 0);
		pWChar = (wchar_t *)malloc(iWCharLen * sizeof(wchar_t));
		CHECK_BREAK(pWChar == nullptr);
		std::memset(pWChar, 0, iWCharLen * sizeof(wchar_t));
		iWCharLen = ::MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pWChar, iWCharLen);
		CHECK_BREAK(iWCharLen == 0);
	} while (false);
	if (iWCharLen > 0)
	{
		wszRet.assign(pWChar);
	}
	SAFE_FREE(pWChar);
#else
	wszRet = UTF8ToWChar(pszSrc);
#endif

	return wszRet;
}
std::wstring CStringUtil::CharToWChar(const std::string& szSrc)
{
	return CharToWChar(szSrc.c_str());
}
std::wstring CStringUtil::UTF8ToWChar(const char* pszSrc)
{
	std::wstring wszRet;
	int iWCharLen = 0;
	wchar_t *pWChar = nullptr;

	do
	{
		assert(pszSrc);
		CHECK_BREAK(pszSrc == nullptr);
		iWCharLen = UTF8ToUnicode_LittleEndian(pszSrc, nullptr);
		CHECK_BREAK(iWCharLen == 0);
		pWChar = (wchar_t *)malloc(iWCharLen * sizeof(wchar_t));
		CHECK_BREAK(pWChar == nullptr);
		iWCharLen = UTF8ToUnicode_LittleEndian(pszSrc, pWChar);
		CHECK_BREAK(iWCharLen == 0);
	} while (false);
	if (iWCharLen > 0)
	{
		wszRet.assign(pWChar);
	}
	SAFE_FREE(pWChar);

	return wszRet;
}
std::wstring CStringUtil::UTF8ToWChar(const std::string& szSrc)
{
	return UTF8ToWChar(szSrc.c_str());
}
std::string  CStringUtil::WCharToChar(const wchar_t *pwszSrc)
{
	std::string szRet;

#if defined(WIN32) || defined(WIN64)
	int iCharLen = 0;
	char* pChar = nullptr;
	do
	{
		assert(pwszSrc);
		CHECK_BREAK(pwszSrc == nullptr);
		iCharLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
		CHECK_BREAK(iCharLen == 0);
		pChar = (char *)malloc(iCharLen + 1);
		CHECK_BREAK(pChar == nullptr);
		std::memset(pChar, 0, iCharLen + 1);
		iCharLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pChar, iCharLen, NULL, NULL);
		CHECK_BREAK(iCharLen == 0);
	} while (false);
	if (iCharLen > 0)
	{
		szRet.assign(pChar);
	}
	SAFE_FREE(pChar);
#else
	szRet = WCharToUTF8(pwszSrc);
#endif

	return szRet;
}
std::string  CStringUtil::WCharToChar(const std::wstring& wszSrc)
{
	return WCharToChar(wszSrc.c_str());
}
std::string  CStringUtil::WCharToUTF8(const wchar_t *pwszSrc)
{
	std::string szRet;
	int iCharLen = 0;
	char* pChar = nullptr;

	do
	{
		assert(pwszSrc);
		CHECK_BREAK(pwszSrc == nullptr);
		iCharLen = UnicodeToUTF8_LittleEndian(pwszSrc, nullptr);
		CHECK_BREAK(iCharLen == 0);
		pChar = (char *)malloc(iCharLen * sizeof(wchar_t));
		CHECK_BREAK(pChar == nullptr);
		iCharLen = UnicodeToUTF8_LittleEndian(pwszSrc, pChar);
		CHECK_BREAK(iCharLen == 0);
	} while (false);
	if (iCharLen > 0)
	{
		szRet.assign(pChar);
	}
	SAFE_FREE(pChar);

	return szRet;
}
std::string  CStringUtil::WCharToUTF8(const std::wstring& wszSrc)
{
	return WCharToUTF8(wszSrc.c_str());
}

/*
// #txt---
   |  Unicode符号范围      |  UTF-8编码方式
 n |  (十六进制)           | (二进制)
---+-----------------------+------------------------------------------------------
 1 | 0000 0000 - 0000 007F |                                              0xxxxxxx
 2 | 0000 0080 - 0000 07FF |                                     110xxxxx 10xxxxxx
 3 | 0000 0800 - 0000 FFFF |                            1110xxxx 10xxxxxx 10xxxxxx
 4 | 0001 0000 - 0010 FFFF |                   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 5 | 0020 0000 - 03FF FFFF |          111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 6 | 0400 0000 - 7FFF FFFF | 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
// #txt---end
// # eg---
   0x00006211 - 我
   | 0000 0800 - 0000 FFFF |                            1110xxxx 10xxxxxx 10xxxxxx
   | 01100010 00010001     |                            11100110 10001000 10010001
   | 11 62 00 00           |                                  e6       88       91
// # eg---end
*/

uint32_t UTF8ToUnicode_LittleEndian(const char* pUtf8, wchar_t* pUnicode) {
	assert(pUtf8 != nullptr);

	uint32_t uLen = 0;
	uint32_t uIndex = 0;
	while (const char& ch = pUtf8[uIndex]) {
		uLen += 1;
		if ((ch & 0x80) == 0) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = pUtf8[uIndex++];
			}
			else {
				uIndex += 1;
			}
		}
		else if ((ch & 0xE0) == 0xC0) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = (pUtf8[uIndex++] & 0x1F) << 6;
				wch |= (pUtf8[uIndex++] & 0x3F);
			}
			else { 
				uIndex += 2;
			}
		}
		else if ((ch & 0xF0) == 0xE0) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = (pUtf8[uIndex++] & 0x0F) << 12;
				wch |= (pUtf8[uIndex++] & 0x3F) << 6;
				wch |= (pUtf8[uIndex++] & 0x3F);
			}
			else {
				uIndex += 3;
			}
		}
		else if ((ch & 0xF8) == 0xF0 && sizeof(wchar_t) > 2) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = (pUtf8[uIndex++] & 0x07) << 18;
				wch |= (pUtf8[uIndex++] & 0x3F) << 12;
				wch |= (pUtf8[uIndex++] & 0x3F) << 6;
				wch |= (pUtf8[uIndex++] & 0x3F);
			}
			else {
				uIndex += 4;
			}
		}
		else if ((ch & 0xFC) == 0xF8 && sizeof(wchar_t) >= 4) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = (pUtf8[uIndex++] & 0x03) << 24;
				wch |= (pUtf8[uIndex++] & 0x3F) << 18;
				wch |= (pUtf8[uIndex++] & 0x3F) << 12;
				wch |= (pUtf8[uIndex++] & 0x3F) << 6;
				wch |= (pUtf8[uIndex++] & 0x3F);
			}
			else {
				uIndex += 5;
			}
		}
		else if ((ch & 0xFE) == 0xFC && sizeof(wchar_t) >= 4) {
			if (pUnicode) {
				wchar_t& wch = pUnicode[uLen - 1];
				wch = (pUtf8[uIndex++] & 0x01) << 30;
				wch |= (pUtf8[uIndex++] & 0x3F) << 24;
				wch |= (pUtf8[uIndex++] & 0x3F) << 18;
				wch |= (pUtf8[uIndex++] & 0x3F) << 12;
				wch |= (pUtf8[uIndex++] & 0x3F) << 6;
				wch |= (pUtf8[uIndex++] & 0x3F);
			}
			else {
				uIndex += 6;
			}
		}
		else {
			uLen = 0;
		}
		if (uLen == 0) {
			break;
		}
	}
	if (uLen > 0) {
		if (pUnicode) {
			pUnicode[uLen] = 0x00;
		}
        uLen++;
	}
	return uLen;
}

uint32_t UnicodeToUTF8_LittleEndian(const wchar_t* pUnicode, char* pUtf8) {
	assert(pUnicode != nullptr);

	uint32_t uLen = 0;
	uint32_t uIndex = 0;
	while (const wchar_t& wch = pUnicode[uIndex]) {
		uIndex += 1;
		if (wch < 0x80) {
			if (pUtf8) {
				pUtf8[uLen++] = (char)wch;
			}
			else {
				uLen += 1;
			}
		}
		else if (wch < 0x800) {
			if (pUtf8) {
				pUtf8[uLen++] = 0xc0 | (wch >> 6);
				pUtf8[uLen++] = 0x80 | (wch & 0x3f);
			}
			else {
				uLen += 2;
			}
		}
		else if (wch < 0x10000) {
			if (pUtf8) {
				pUtf8[uLen++] = 0xe0 | (wch >> 12);
				pUtf8[uLen++] = 0x80 | ((wch >> 6) & 0x3f);
				pUtf8[uLen++] = 0x80 | (wch & 0x3f);
			}
			else {
				uLen += 3;
			}
		}
		else if (wch < 0x200000){
			if (pUtf8) {
				pUtf8[uLen++] = 0xf0 | (wch >> 18);
				pUtf8[uLen++] = 0x80 | ((wch >> 12) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 6) & 0x3f);
				pUtf8[uLen++] = 0x80 | (wch & 0x3f);
			}
			else {
				uLen += 4;
			}
		}
		else if (wch < 0x4000000) {
			if (pUtf8) {
				pUtf8[uLen++] = 0xf8 | (wch >> 24);
				pUtf8[uLen++] = 0x80 | ((wch >> 18) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 12) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 6) & 0x3f);
				pUtf8[uLen++] = 0x80 | (wch & 0x3f);
			}
			else {
				uLen += 5;
			}
		}
		else if (wch < 0x80000000) {
			if (pUtf8) {
				pUtf8[uLen++] = 0xfc | (wch >> 30);
				pUtf8[uLen++] = 0x80 | ((wch >> 24) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 18) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 12) & 0x3f);
				pUtf8[uLen++] = 0x80 | ((wch >> 6) & 0x3f);
				pUtf8[uLen++] = 0x80 | (wch & 0x3f);
			}
			else {
				uLen += 6;
			}
		}
		else {
			uLen = 0;
		}
		if (uLen == 0) {
			break;
		}
	}
	if (uLen > 0) {
		if (pUtf8) {
			pUtf8[uLen] = 0x00;
		}
		uLen++;
	}
	return uLen;
}
