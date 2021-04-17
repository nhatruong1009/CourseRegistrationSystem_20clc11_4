#include"CommonFunc.h"
#include <windows.h>
void _LText()
{
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
} 
void _SText() {
	_setmode(_fileno(stdin), _O_TEXT);
	_setmode(_fileno(stdout), _O_TEXT);
}
void LStrToStr(char desination[], int size, std::wstring source) {
	for (int i = 0; i < size; i++) {
		desination[i] = source[i];
	}
}
void LStrToStr(char desination[], int size, wchar_t* source) {
	for (int i = 0; i < size; i++) {
		desination[i] = source[i];
	}
}
void StrToLStr(wchar_t desination[], int size, std::string source) {
	for (int i = 0; i < size; i++) {
		desination[i] = source[i];
	}
}
void StrToLStr(wchar_t desination[], int size, char* source) {
	for (int i = 0; i < size; i++) {
		desination[i] = source[i];
	}
}
void StrCat(char*&destination, int size, std::string source) {
	int n = strlen(destination);
	char* temp = new char[n + size + 1];
	temp[n + size] = '\0';
	for (int i = 0; i < n; i++) {
		temp[i] = destination[i];
	}
	for (int i = n; i < size + n; i++) {
		temp[i] = source[i - n];
	}
	delete destination;
	destination = temp;
}
void StrCat(char*& destination, int size, char* source) {
	int n = strlen(destination);
	char* temp = new char[n + size + 1];
	temp[n + size] = '\0';
	for (int i = 0; i < n; i++) {
		temp[i] = destination[i];
	}
	for (int i = n; i < size + n; i++) {
		temp[i] = source[i - n];
	}
	delete destination;
	destination = temp;
}
void StrCat(wchar_t*& destination, int size, std::wstring source) {
	int n = wcslen(destination);
	wchar_t* temp = new wchar_t[n + size + 1];
	temp[n + size] = L'\0';
	for (int i = 0; i < n; i++) {
		temp[i] = destination[i];
	}
	for (int i = n; i < size + n; i++) {
		temp[i] = source[i - n];
	}
	delete destination;
	destination = temp;
}
void StrCat(wchar_t*& destination, int size, wchar_t* source) {
	int n = wcslen(destination);
	wchar_t* temp = new wchar_t[n + size + 1];
	temp[n + size] = L'\0';
	for (int i = 0; i < n; i++) {
		temp[i] = destination[i];
	}
	for (int i = n; i < size + n; i++) {
		temp[i] = source[i - n];
	}
	delete destination;
	destination = temp;
}
wchar_t* StrCat(wchar_t* source1, wchar_t* source2) {
	int n = wcslen(source1), m = wcslen(source2);
	wchar_t* result = new wchar_t[n + m + 1];
	result[n + m ] = L'\0';
	for (int i = 0; i < n ; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
wchar_t* StrCat(wchar_t* source1,std::wstring source2) {
	int n = wcslen(source1), m =source2.length();
	wchar_t* result = new wchar_t[n + m + 1];
	result[n + m] = L'\0';
	for (int i = 0; i < n ; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
char* StrCat(char* source1, char* source2) {
	int n = strlen(source1), m = strlen(source2);
	char* result = new char[n + m + 1];
	result[n + m] = L'\0';
	for (int i = 0; i < n; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
char* StrCat(char* source1, std::string source2) {
	int n = strlen(source1), m = source2.length();
	char* result = new char[n + m + 1];
	result[n + m] = L'\0';
	for (int i = 0; i < n; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
__int64 StringToInt(wchar_t* ch) {
	unsigned __int64 a = 0;
	while (*ch != L'\0')
	{
		a = a * 10 + *ch - L'0';
		ch++;
	}
	return a;
}
__int64 StringToInt(char* ch) {
	unsigned __int64 a = 0;
	while (*ch != L'\0')
	{
		a = a * 10 + *ch - '0';
		ch++;
	}
	return a;
}
__int64 StringToInt(std::wstring str) {
	unsigned __int64 a = 0;
	for (int i = 0; i < str.length(); i++) {
		a = a * 10 + str[i] - L'0';
	}
	return a;
}
__int64 StringToInt(std::string str) {
	unsigned __int64 a = 0;
	for (int i = 0; i < str.length(); i++) {
		a = a * 10 + str[i] - '0';
	}
	return a;
}
Date StringToDate(wchar_t* ch) {
	Date a;
	int beg = 0;
	int end = 0;
	while (ch[end] != L'\0' && ch[end] != L'/')
	{
		end += 1;
	}
	if (ch[end] != L'\0') {
		for (; beg < end; beg++) {
			a.dd = a.dd * 10 + ch[beg] - L'0';
		}
		beg = end + 1;
		end += 1;
		while (ch[end] != L'\0' && ch[end] != L'/')
		{
			end += 1;
		}
		if (ch[end] != L'\0') {
			for (; beg < end; beg++) {
				a.mm = a.mm * 10 + ch[beg] - L'0';
			}
			beg = end + 1;
			end += 1;
			while (ch[end] != L'\0')
			{
				end += 1;
			}
			for (; beg < end; beg++) {
				a.yy = a.yy * 10 + ch[beg] - L'0';
			}
			return a;
		}
	}
	Date undentity;
	return undentity;
}
Date StringToDate(char* ch) {
	Date a;
	int beg = 0;
	int end = 0;
	while (ch[end] != '\0' && ch[end] != '/')
	{
		end += 1;
	}
	if (ch[end] != '\0') {
		for (; beg < end; beg++) {
			a.dd = a.dd * 10 + ch[beg] - '0';
		}
		beg = end + 1;
		end += 1;
		while (ch[end] != '\0' && ch[end] != '/')
		{
			end += 1;
		}
		if (ch[end] != '\0') {
			for (; beg < end; beg++) {
				a.mm = a.mm * 10 + ch[beg] - '0';
			}
			beg = end + 1;
			end += 1;
			while (ch[end] != '\0')
			{
				end += 1;
			}
			for (; beg < end; beg++) {
				a.yy = a.yy * 10 + ch[beg] - L'0';
			}
			return a;
		}
	}
	Date undentity;
	return undentity;
}
 char* NumToStr(unsigned __int64 num) {
	int n = ceil(log10f(num));
	unsigned __int64 temp = num;
	char* result = new char[n + 1];
	result[n] = '\0';
	for (int i = n - 1; i >= 0; i--) {
		result[i] = temp % 10 + '0';
		temp = temp / 10;
	}
	return result;
}
wchar_t* NumToLStr(unsigned __int64 num) {
	int n = ceil(log10f(num));
	unsigned __int64 temp = num;
	wchar_t* result = new wchar_t[n + 1];
	result[n] = L'\0';
	for (int i = n - 1; i >= 0; i--) {
		result[i] = temp % 10 + L'0';
		temp = temp / 10;
	}
	return result;
}
tm GetTime()
{
	__time32_t now = time(0);
	tm t;
	_localtime32_s(&t, &now);
	t.tm_year += 1900;
	t.tm_mon += 1;
	return t;
}
bool operator>(tm& t1, tm& t2)
{
	time_t a, b;
	a = mktime(&t1);
	b = mktime(&t2);
	if (a > b) return 1;
	else return 0;
}
bool operator<(tm& t1, tm& t2)
{
	time_t a, b;
	a = mktime(&t1);
	b = mktime(&t2);
	if (a < b) return 1;
	else return 0;
}
void SaveLoginHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\login.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}


char* AddTwoStr(const char* a, char* b) {
	int l1 = strlen(a), l2 = strlen(b);
	int n = l1 + l2;
	char* result = new char[n + 1];
	result[n] = '\0';
	for(int i=0;i<l1;i++){
		result[i] = a[i];
	}
	for (int i = l1; i < n; i++) {
		result[i] = b[i - l1];
	}
	return result;
}
wchar_t* AddTwoStr(const wchar_t* a, wchar_t* b) {
	int l1 = wcslen(a), l2 = wcslen(b);
	int n = l1 + l2;
	wchar_t* result = new wchar_t[n + 1];
	result[n] = '\0';
	for (int i = 0; i < l1; i++) {
		result[i] = a[i];
	}
	for (int i = l1; i < n; i++) {
		result[i] = b[i - l1];
	}
	return result;
}
std::string AddTwoStr(std::string a, std::string b) {
	std::string result;
	int n = a.length();
	int m = b.length();
	result.resize(n + m);
	for (int i = 0; i < n; i++) {
		result[i] = a[i];
	}
	for (int i = 0; i < m; i++) {
		result[n + i] = b[i];
	}
	return result;
}
std::wstring AddTwoStr(std::wstring a, std::wstring b) {
	std::wstring result;
	int n = a.length();
	int m = b.length();
	result.resize(n + m);
	for (int i = 0; i < n; i++) {
		result[i] = a[i];
	}
	for (int i = 0; i < m; i++) {
		result[n + i] = b[i];
	}
	return result;
}
char* StrToChar(std::string source) {
	int n = source.length();
	char* result = new char[n + 1];
	result[n] = '\0';
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}

std::string ToString(std::wstring source) {
	std::string result;
	int n = source.length();
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
std::string ToString(wchar_t* source) {
	std::string result;
	int n = wcslen(source);
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
std::string ToString(char* source) {
	std::string result;
	int n = strlen(source);
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
std::wstring ToWstring(std::string source) {
	std::wstring result;
	int n = source.length();
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
std::wstring ToWstring(char* source) {
	std::wstring result;
	int n = strlen(source);
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
std::wstring ToWstring(wchar_t* source) {
	std::wstring result;
	int n = wcslen(source);
	result.resize(n);
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}


Filelist* TakeFileInFolder(const std::wstring& name)
{
	Filelist* result = nullptr;
	std::wstring pattern(name);
	pattern.append(L"\\*");
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			AddInListFile(result, ToString(data.cFileName));
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	return result;
}
Filelist* TakeFileInFolder(const std::string& name) {
	return TakeFileInFolder(ToWstring(name));
}