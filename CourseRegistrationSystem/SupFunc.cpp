#include"Sup.h"


void _LText()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	return;
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

void StrCat(char*& destination, int size, std::string source) {
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
char* StrToChar(std::string source) {
	int n = source.length();
	char* result = new char[n + 1];
	result[n] = '\0';
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
char* AddTwoStr(const char* a, const char* b) {
	int l1 = strlen(a), l2 = strlen(b);
	int n = l1 + l2;
	char* result = new char[n + 1];
	result[n] = '\0';
	for (int i = 0; i < l1; i++) {
		result[i] = a[i];
	}
	for (int i = l1; i < n; i++) {
		result[i] = b[i - l1];
	}
	return result;
}

wchar_t* StrCat(wchar_t* source1, wchar_t* source2) {
	int n = wcslen(source1), m = wcslen(source2);
	wchar_t* result = new wchar_t[n + m + 1];
	result[n + m] = L'\0';
	for (int i = 0; i < n; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
wchar_t* StrCat(wchar_t* source1, std::wstring source2) {
	int n = wcslen(source1), m = source2.length();
	wchar_t* result = new wchar_t[n + m + 1];
	result[n + m] = L'\0';
	for (int i = 0; i < n; i++) {
		result[i] = source1[i];
	}
	for (int i = 0; i < m; i++) {
		result[i + n] = source2[i];
	}
	return result;
}
wchar_t* StrToChar(std::wstring source) {
	int n = source.length();
	wchar_t* result = new wchar_t[n + 1];
	result[n] = L'\0';
	for (int i = 0; i < n; i++) {
		result[i] = source[i];
	}
	return result;
}
wchar_t* AddTwoStr(const wchar_t* a, const wchar_t* b) {
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
void RemoveSpace(wchar_t* a)
{
	std::wstring temp = ToWstring(a);

	// Delete first spaces
	short space = 0;
	for (int j = 0; temp[j] == L' '; j++)
		space++;
	temp.erase(0, space);

	// Delete the remainings
	int i = 0;
	int pos = 0;
	while (1)
	{
		pos = temp.find_first_of(L' ', i) + 1;
		if (pos == 0)
			break;
		i = pos;
		while (temp[i] == ' ')
			i++;
		temp.erase(pos, i - pos);
		i = pos; // set i back cause string strink
	}
	delete[]a;

}

std::string InputHidden() {
	char temp;
	std::string pass;
	while (true)
	{
		temp = _getwch();
		if (temp == KEY_ENTER) break;
		else if (temp == KEY_ESC) return "";
		if (temp == KEY_BACKSPACE) {
			if (pass.size() != 0) {
				pass.pop_back();
				std::cout << temp << ' ' << temp;
			}
		}
		if (temp >= ' ' && temp <= '~') {
			std::cout << "*";
			pass.push_back(temp);
		}
	}
	std::cout << '\n';
	return pass;
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
std::string NumToStr(unsigned __int64 num) {
	if (num == 0) return { "" };
	int n = ceil(log10f(num));
	unsigned __int64 temp = num;
	std::string result;
	result.resize(n);
	for (int i = n - 1; i >= 0; i--) {
		result[i] = temp % 10 + '0';
		temp = temp / 10;
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
std::wstring NumToLStr(unsigned __int64 num) {
	if (num == 0) return { L"" };
	int n = ceil(log10f(num));
	unsigned __int64 temp = num;
	std::wstring result;
	result.resize(n);
	for (int i = n - 1; i >= 0; i--) {
		result[i] = temp % 10 + L'0';
		temp = temp / 10;
	}
	return result;
}

unsigned __int64 InputNumber() {
	char temp;
	std::string pass;
	while (true)
	{
		temp = _getwch();
		if (temp == KEY_ENTER) break;
		else if (temp == KEY_ESC) return -1;
		if (temp == KEY_BACKSPACE) {
			if (pass.size() != 0) {
				pass.pop_back();
				std::cout << temp << ' ' << temp;
			}
		}
		if (temp >= '0' && temp <= '9') {
			std::cout << temp;
			pass.push_back(temp);
		}
	}
	std::cout << '\n';
	return StringToInt(pass);
}
unsigned __int64 StringToInt(wchar_t* ch) {
	unsigned __int64 a = 0;
	while (*ch != L'\0')
	{
		a = a * 10 + *ch - L'0';
		ch++;
	}
	return a;
}
unsigned __int64 StringToInt(char* ch) {
	unsigned __int64 a = 0;
	while (*ch != L'\0')
	{
		a = a * 10 + *ch - '0';
		ch++;
	}
	return a;
}
unsigned __int64 StringToInt(std::wstring str) {
	unsigned __int64 a = 0;
	for (int i = 0; i < str.length(); i++) {
		a = a * 10 + str[i] - L'0';
	}
	return a;
}
unsigned __int64 StringToInt(std::string str) {
	unsigned __int64 a = 0;
	for (int i = 0; i < str.length(); i++) {
		a = a * 10 + str[i] - '0';
	}
	return a;
}

Date StringToDate(const wchar_t* ch) {
	int n = wcslen(ch);
	int i = 0;
	Date result{ 0,0,0 };
	for (; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.dd = result.dd * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.mm = result.mm * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.yy = result.yy * 10 + ch[i] - '0';
		else break;
	}
	return result;
}
Date StringToDate(const char* ch) {
	int n = strlen(ch);
	int i = 0;
	Date result{ 0,0,0 };
	for (; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.dd = result.dd * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.mm = result.mm * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.yy = result.yy * 10 + ch[i] - '0';
		else break;
	}
	return result;
}
Date StringToDate(std::wstring ch) {
	int n = ch.length();
	int i = 0;
	Date result{ 0,0,0 };
	for (; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.dd = result.dd * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.mm = result.mm * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.yy = result.yy * 10 + ch[i] - '0';
		else break;
	}
	return result;
}
Date StringToDate(std::string ch) {
	int n = ch.length();
	int i = 0;
	Date result{ 0,0,0 };
	for (; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.dd = result.dd * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.mm = result.mm * 10 + ch[i] - '0';
		else break;
	}
	for (i = i + 1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.yy = result.yy * 10 + ch[i] - '0';
		else break;
	}
	return result;
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
void DealocatedArrString(char**& stringarr) {
	int n = _msize(stringarr) / sizeof(char*);
	for (int i = 0; i < n; i++) {
		delete[] stringarr[i];
	}
	delete[] stringarr;
	stringarr = nullptr;
}
void DealocatedArrString(wchar_t**& stringarr) {
	int n = _msize(stringarr) / sizeof(wchar_t*);
	for (int i = 0; i < n; i++) {
		delete[] stringarr[i];
	}
	delete[] stringarr;
	stringarr = nullptr;
}










