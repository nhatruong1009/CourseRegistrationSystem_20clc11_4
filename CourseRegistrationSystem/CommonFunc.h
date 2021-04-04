#ifndef _CommonFunc
#define _CommonFunc
#include<io.h>
#include"Data.h"
#include<iostream>
#include <fcntl.h>
#include<fstream>
#include<ctime>
#include<locale>
void _LText();
void _SText();
void LStrToStr(char desination[], int size, std::wstring source);
void LStrToStr(char desination[], int size, wchar_t* source);
void StrToLStr(wchar_t desination[], int size, std::string source);
void StrToLStr(wchar_t desination[], int size, char* source);
void StrCat(char*& destination, int size, std::string source);
void StrCat(char*& destination, int size, char* source);
void StrCat(wchar_t*& destination, int size, std::wstring source);
void StrCat(wchar_t*& destination, int size, wchar_t* source);
__int64 StringToInt(wchar_t* ch);
__int64 StringToInt(char* ch);
__int64 StringToInt(std::wstring str);
char* NumToStr(unsigned __int64 num);
Date StringToDate(wchar_t* ch);
Date StringToDate(char* ch);
tm GetTime();
bool operator>(tm& t1, tm& t2);
bool operator<(tm& t1, tm& t2);
void SaveLoginHistory(char* AccountUsername);
#endif // !_Common
