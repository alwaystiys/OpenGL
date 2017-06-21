#include "Common/basic_util.h"

#include <iostream>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#endif
bool ReadFile(const char *pFilename, string& outFile) {
    ifstream f(pFilename);
    bool ret = false;
    if(f.is_open()) {
        string line;
        while(getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }
        f.close();
        ret = true;
    } else {
    }
    return ret;
}


void ThrowError(const char* pFileName, unsigned int line, const char* pError) {
#ifdef WIN32
    char msg[1000];
    _snprintf_s(msg, sizeof(msg), "%s:%d: %s", pFileName, line, pError);
    MessageBoxA(NULL, msg, NULL, 0);
#else
    fprintf(stderr, "%s:%d: %s\n", pFileName, line, pError);
#endif
}