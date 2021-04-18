#ifndef _CommonFunc
#define _CommonFunc
#include<io.h>
#include"Data.h"
#include<iostream>
#include <fcntl.h>
#include<fstream>
#include<ctime>
#include<locale>

#define KEY_UP 72 //phím di chuyển lên
#define KEY_DOWN 80 //phím di chuyển xuống
#define KEY_LEFT 75 //phím di chuyển trái
#define KEY_RIGHT 77 //phím di chuyển phải
#define KEY_ENTER 13//phim enter
#define KEY_ESC 27// phim esc

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
wchar_t* StrCat(wchar_t* destination, wchar_t* source);
wchar_t* StrCat(wchar_t* source1, std::wstring source2);
char* StrCat(char* destination, char* source);
char* StrCat(char* source1, std::string source2);

std::string ToString(std::wstring source);
std::string ToString(wchar_t* source);
std::string ToString(char* source);
std::wstring ToWstring(std::string source);
std::wstring ToWstring(char* source);
std::wstring ToWstring(wchar_t* source);

__int64 StringToInt(wchar_t* ch);
__int64 StringToInt(char* ch);
__int64 StringToInt(std::wstring str);
__int64 StringToInt(std::string str);

char* NumToStr(unsigned __int64 num);
wchar_t* NumToLStr(unsigned __int64 num);
Date StringToDate(wchar_t* ch);
Date StringToDate(char* ch);

tm GetTime();
bool operator>(tm& t1, tm& t2);
bool operator<(tm& t1, tm& t2);
void SaveLoginHistory(char* AccountUsername);

char* AddTwoStr(const char* a, char* b);
wchar_t* AddTwoStr(const wchar_t* a, wchar_t* b);
std::string AddTwoStr(std::string a, std::string b);
std::wstring AddTwoStr(std::wstring a, std::wstring b);
char* StrToChar(std::string source);

Filelist* TakeFileInFolder(const std::wstring& name);
Filelist* TakeFileInFolder(const std::string& name);
short Menu(wchar_t** list, short Xposition, short Yposition);
short Choose(wchar_t** list, short X, short Y);
#endif