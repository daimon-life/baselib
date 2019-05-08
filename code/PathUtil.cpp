#include <cassert>
#include <string>

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

#if defined(__linux__) || defined(LINUX)
#include <unistd.h>
#include <limits.h>
#endif

#if defined(__APPLE__) || defined(MACOS)
#include <mach-o/dyld.h>
#include <limits.h>
#endif


//
std::string GetExecutePath()
{
    std::string szRet;
    
#if defined(WIN32) || defined(WIN64)
    char szExePath[MAX_PATH] = { 0 };
    DWORD len = ::GetModuleFileNameA(NULL, szExePath, sizeof(szExePath));
    szExePath[len] = '\0';
    szRet = szExePath;
#endif
    
#if defined(__linux__) || defined(LINUX)
    char szExePath[PATH_MAX];
    ssize_t len = ::readlink("/proc/self/exe", szExePath, sizeof(szExePath));
    if (len == -1 || len == sizeof(szExePath))
        len = 0;
    szExePath[len] = '\0';
    szRet = szExePath;
#endif
    
#if defined(__APPLE__) || defined(MACOS)
    char szExePath[PATH_MAX] = { 0 };
    uint32_t len = sizeof(szExePath);
    if (_NSGetExecutablePath(szExePath, &len) != 0)
    {
        szExePath[0] = '\0';
    }
    else
    {
        char* canonicalPath = realpath(szExePath, NULL);
        if (canonicalPath != NULL)
        {
            strncpy(szExePath, canonicalPath, len);
            free(canonicalPath);
        }
    }
    szRet = szExePath;
#endif
    
    return szRet;
}


//
std::string GetGetExecuteDir()
{
    std::string szRet = GetExecutePath();
    
#if defined(WIN32) || defined(WIN64)
    szRet = szRet.substr(0, szRet.rfind('\\') + 1);
#else
    szRet = szRet.substr(0, szRet.rfind('/') + 1);
#endif
    
    return szRet;
}

std::string GetGetExecuteName()
{
    std::string szRet = GetExecutePath();
    
#if defined(WIN32) || defined(WIN64)
    szRet = szRet.substr(szRet.rfind('\\') + 1, szRet.size() - 1);
#else
    szRet = szRet.substr(szRet.rfind('/') + 1, szRet.size() - 1);
#endif
    
    return szRet;
}

