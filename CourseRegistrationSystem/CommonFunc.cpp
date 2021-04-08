#include"CommonFunc.h"

void _LText()
{
	_setmode(_fileno(stdin), _O_U8TEXT);
	_setmode(_fileno(stdout), _O_U8TEXT);
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
	int n = 0;
	unsigned __int64 temp = num;
	for (; num != 0; n++) {
		num = num / 10;
	}
	char* result = new char[n + 1];
	result[n] = '\0';
	for (int i = n - 1; i >= 0; i--) {
		result[i] = temp % 10 + '0';
		temp = temp / 10;
	}
	return result;
}

tm GetTime()
{
	__time32_t now = time(0);
	tm t;
	_localtime32_s(&t, &now);
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
	file.open("login.txt", std::ios::app);
	file << AccountUsername << " " << a << std::endl;
	file.close();
}
