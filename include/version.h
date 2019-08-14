#pragma once

#define FILE_VERSION                    1, 0, 0, 0
#define FILE_VERSION_STRING_T1(ver)     #ver
#define FILE_VERSION_STRING_T2(ver)     FILE_VERSION_STRING_T1(ver)
#define FILE_VERSION_STRING             FILE_VERSION_STRING_T2(FILE_VERSION)
