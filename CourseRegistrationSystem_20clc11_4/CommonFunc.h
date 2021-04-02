#ifndef _CommonFunc
#define _CommonFunc
#include<io.h>
#include<iostream>
#include <fcntl.h>
void _LText();
void _SText();
void LStrToStr(char desination[], int size, std::wstring source);
void LStrToStr(char desination[], int size, wchar_t* source);
void StrToLStr(wchar_t desination[], int size, std::string source);
void StrToLStr(wchar_t desination[], int size, char* source);
__int64 StringToInt(wchar_t* ch);
__int64 StringToInt(char* ch);
__int64 StringToInt(std::wstring str);
Date StringToDate(wchar_t* ch);
Date StringToDate(char* ch);
#endif // !_Common
