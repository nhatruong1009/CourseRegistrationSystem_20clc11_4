#ifndef _CommonFunc
#define _CommonFunc
#include<io.h>
#include"Data.h"
#include<iostream>
#include <fcntl.h>
#include<fstream>
#include<ctime>
#include<locale>

#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_LEFT 75 
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8//

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

wchar_t* StrToChar(std::wstring str);
char* StrToChar(std::string str);

std::string ToString(std::wstring source);
std::string ToString(wchar_t* source);
std::string ToString(char* source);
std::wstring ToWstring(std::string source);
std::wstring ToWstring(char* source);
std::wstring ToWstring(wchar_t* source);

unsigned __int64 StringToInt(wchar_t* ch);
unsigned __int64 StringToInt(char* ch);
unsigned __int64 StringToInt(std::wstring str);
unsigned __int64 StringToInt(std::string str);

char* NumToStr(unsigned __int64 num);
wchar_t* NumToLStr(unsigned __int64 num);
Date StringToDate(const wchar_t* ch);
Date StringToDate(const char* ch);
Date StringToDate(std::wstring ch);
Date StringToDate(std::string ch);
Date GetTime();
bool operator>(tm& t1, tm& t2);
bool operator<(tm& t1, tm& t2);
void SaveLoginHistory(char* AccountUsername);

char* AddTwoStr(const char* a, const char* b);
wchar_t* AddTwoStr(const wchar_t* a, const wchar_t* b);
std::string AddTwoStr(std::string a, std::string b);
std::wstring AddTwoStr(std::wstring a, std::wstring b);
char* StrToChar(std::string source);

Filelist* TakeFileInFolder(const std::wstring& name);
Filelist* TakeFileInFolder(const std::string& name);
void DeleteCurFileList(Filelist*& filelist);

void DealocatedArrString(char**& stringarr);
void DealocatedArrString(wchar_t**& stringarr);

void GotoXY(short x, short y);
short Menu(wchar_t** list, short Xposition, short Yposition);
short Choose(wchar_t** list, short X, short Y);
short Menu(char** list, short Xposition, short Yposition);
short Choose(char** list, short X, short Y);
std::string ChoseFolder(Filelist* list, short x, short y);
std::string InputHidden();
unsigned __int64 InputNumber();
Date InputDate();
bool LeapYear(int y);
bool CheckDate(Date dat);
#endif