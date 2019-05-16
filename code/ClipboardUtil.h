#pragma once


#ifndef _CLIPBOARD_UTIL_H_
#define _CLIPBOARD_UTIL_H_


#include <string>


class CClipboardUtil
{
public:
	static bool         Copy(std::wstring szContent);
	static std::wstring Paste();

protected:
	CClipboardUtil() {};
	~CClipboardUtil() {};
};

#endif // _CLIPBOARD_UTIL_H_
