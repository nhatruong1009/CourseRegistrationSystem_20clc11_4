#ifndef _Sup
#define _Sup
#include"Data.h"
#include<locale>
#include <fcntl.h>
#include<io.h>
//***Some Key***
#define KEY_UP 72 
#define KEY_DOWN 80
#define KEY_LEFT 75 
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_BACKSPACE 8

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

char* StrCat(char* destination, char* source);
char* StrCat(char* source1, std::string source2);
char* StrToChar(std::string str);
char* AddTwoStr(const char* a, const char* b);

wchar_t* StrCat(wchar_t* destination, wchar_t* source);
wchar_t* StrCat(wchar_t* source1, std::wstring source2);
wchar_t* StrToChar(std::wstring str);
wchar_t* AddTwoStr(const wchar_t* a, const wchar_t* b);
void RemoveSpace(wchar_t* a);

std::string InputHidden();
std::string ToString(std::wstring source);
std::string ToString(wchar_t* source);
std::string ToString(char* source);
std::string NumToStr(unsigned __int64 num);

std::wstring ToWstring(std::string source);
std::wstring ToWstring(char* source);
std::wstring ToWstring(wchar_t* source);
std::wstring NumToLStr(unsigned __int64 num);

unsigned __int64 InputNumber();
unsigned __int64 StringToInt(wchar_t* ch);
unsigned __int64 StringToInt(char* ch);
unsigned __int64 StringToInt(std::wstring str);
unsigned __int64 StringToInt(std::string str);

Date StringToDate(const wchar_t* ch);
Date StringToDate(const char* ch);
Date StringToDate(std::wstring ch);
Date StringToDate(std::string ch);

bool operator>(tm& t1, tm& t2);
bool operator<(tm& t1, tm& t2);

void DealocatedArrString(char**& stringarr);
void DealocatedArrString(wchar_t**& stringarr);


#endif // !_SupFunc
