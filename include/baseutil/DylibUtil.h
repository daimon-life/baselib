#pragma once

#ifndef _DYLIB_UTIL_H_
#define _DYLIB_UTIL_H_

// dynamic or share library handle class
class CDylibUtil
{
public:
	static void* LoadDylib(const char* pszDylibPath);
	static void  FreeDylib(void* hDylib);
	static void* ReadDylib(void* hDylib, const char* pszSymbol);

	CDylibUtil() = delete;
	~CDylibUtil() = delete;
};

#endif // _DYLIB_UTIL_H_
