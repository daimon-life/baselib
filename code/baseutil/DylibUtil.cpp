#include "DylibUtil.h"

#include <string>
#include <cassert>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

#if defined(__linux__) || defined(__APPLE__)
#include <dlfcn.h>
#endif

std::string GetLastErrorString();

void* CDylibUtil::LoadDylib(const char *pszDylibPath)
{
	void* pDylib = nullptr;

#if defined(WIN32) || defined(WIN64)
	std::string szError;
	pDylib = LoadLibraryA(pszDylibPath);
	if (pDylib == nullptr)
	{
		szError = GetLastErrorString();
	}
#endif

#if defined(__linux__) || defined(__APPLE__)
	std::string szError;
	pDylib = dlopen(pszDylibPath, RTLD_LAZY);
	if (pDylib == nullptr)
	{
		szError = dlerror();
	}
#endif

	return pDylib;
}

void CDylibUtil::FreeDylib(void* hDylib)
{

#if defined(WIN32) || defined(WIN64)
	FreeLibrary(static_cast<HMODULE>(hDylib));
#endif

#if defined(__linux__) || defined(__APPLE__)
	dlclose(hDylib);
#endif

}

void* CDylibUtil::ReadDylib(void* hDylib, const char* pszSymbol)
{
	void* pFunc = nullptr;

#if defined(WIN32) || defined(WIN64)
	std::string szError;
	pFunc = GetProcAddress(static_cast<HMODULE>(hDylib), pszSymbol);
	if (pFunc == nullptr)
	{
		szError = GetLastErrorString();
	}
#endif

#if defined(__linux__) || defined(__APPLE__)
	std::string szError;
	pFunc = dlsym(hDylib, pszSymbol);
	if (pFunc == nullptr)
	{
		szError = dlerror();
	}
#endif

	return pFunc;
}

std::string GetLastErrorString()
{
	std::string szRet;

	HANDLE hLocalError = nullptr;
	DWORD dwFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS;
	DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);
	FormatMessageA(dwFlag, nullptr, GetLastError(), dwLanguageId, (LPSTR)&hLocalError, 0, nullptr);
	szRet = static_cast<char*>(LocalLock(hLocalError));
	LocalFree(hLocalError);

	return szRet;
}
