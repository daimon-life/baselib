#include "ClipboardUtil.h"

#include <cassert>
#include <string>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

bool CClipboardUtil::Copy(std::wstring szContent)
{
	bool bRet = false;

	if (szContent.length() > 0)
	{
#if defined(WIN32) || defined(WIN64)
		do 
		{
			// open
			BOOL bOpen = OpenClipboard(NULL);
			if (!bOpen) break;
			// alloc
			size_t nCount = wcslen(szContent.c_str());
			size_t nlen = (nCount + 1) * sizeof(wchar_t);
			HANDLE hData = GlobalAlloc(GMEM_MOVEABLE, nlen);
			if (!hData)
			{
				CloseClipboard();
			}
			if (!hData) break;
			// copy
			EmptyClipboard();
			LPWSTR pData = (LPWSTR)GlobalLock(hData);
			memcpy(pData, szContent.c_str(), nCount * sizeof(wchar_t));
			pData[nCount] = (wchar_t)0;
			GlobalUnlock(hData);
			SetClipboardData(CF_UNICODETEXT, hData);
			// close
			CloseClipboard();
		} while (false);
#endif
	}
	return bRet;
}

std::wstring CClipboardUtil::Paste()
{
	std::wstring wszRet;

#if defined(WIN32) || defined(WIN64)
	do 
	{
		// open
		BOOL bOpen = OpenClipboard(NULL);
		if (!bOpen) break;
		// fetch
		HANDLE hMem = GetClipboardData(CF_UNICODETEXT);
		if (!hMem)
		{
			CloseClipboard();
		}
		if (!hMem) break;
		wchar_t* lpStr = (wchar_t*)GlobalLock(hMem);
		if (lpStr == nullptr) break;
		while (*lpStr)
		{
			wszRet.append(1, *lpStr);
			lpStr++;
		}
		GlobalUnlock(hMem);
		// close
		CloseClipboard();
	} while (false);
#endif

	return wszRet;
}
