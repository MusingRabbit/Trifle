#ifndef SYSUTIL_H
#define SYSUTIL_H

#include <string>

#ifndef WIN32
#include <cxxabi.h>
#else
#include <windows.h>
#include <DbgHelp.h>
#endif

class SysUtil
{
  public:
#ifndef WIN32
    static inline std::string Demangle(const std::string& name)
    {
        int status = 0;
        char* p = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
        std::string ret(p);
        free(p);
        return ret;
    }

#else
    static inline std::string Demangle(const std::string& name)
    {
        TCHAR szUndecorateName[256];
        memset(szUndecorateName, 0, 256);
        UnDecorateSymbolName(name.c_str(), szUndecorateName, 256, 0);
        return szUndecorateName;
    }

#endif
};
#endif