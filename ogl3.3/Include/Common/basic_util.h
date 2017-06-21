
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <assert.h>

using namespace std;


#define GLCheckError() (glGetError() == GL_NO_ERROR)

bool ReadFile(const char *pFilename, string& outFile);
void ThrowError(const char* pFileName, unsigned int line, const char* pError);