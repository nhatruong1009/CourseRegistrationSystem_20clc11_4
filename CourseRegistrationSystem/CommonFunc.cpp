#include"CommonFunc.h"
#include <windows.h>
#include<string>
void _LText()
{
	_setmode(_fileno(stdin), _O_U16TEXT); 
	_setmode(_fileno(stdout), _O_U16TEXT);
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
	for (i=i+1; i < n; i++) {
		if (ch[i] <= '9' && ch[i] >= '0') result.mm = result.mm * 10 + ch[i] - '0';
		else break;
	}
	for (i=i+1; i < n; i++) {
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

 char* NumToStr(unsigned __int64 num) {
	if (num == 0) return new char[]{ "0\0" };
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
	if (num == 0) return new wchar_t[] { L"0\0" };
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
Date GetTime()
{
	__time32_t now = time(0);
	tm t;
	_localtime32_s(&t, &now);
	t.tm_year += 1900;
	t.tm_mon += 1;
	Date temp;
	temp.dd = t.tm_mday;
	temp.mm = t.tm_mon;
	temp.yy = t.tm_year;
	return temp;
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


char* AddTwoStr(const char* a, const char* b) {
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

wchar_t* StrToChar(std::wstring source) {
	int n = source.length();
	wchar_t* result = new wchar_t[n + 1];
	result[n] = L'\0';
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
		for (int i = 0; i < 2; i++) {
			FindNextFile(hFind, &data);
		}
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

void DeleteCurFileList(Filelist*& filelist) {
	if (filelist->pNext == filelist) {
		delete filelist;
		filelist = nullptr;
	}
	else {
		Filelist* filedel = filelist;
		filelist = filelist->pNext;
		filedel->pPrev->pNext = filedel->pNext;
		filedel->pNext->pPrev = filedel->pPrev;
		delete filedel;
	}
}

void GotoXY(short x, short y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

short Menu(wchar_t** list, short Xposition, short Yposition) {
	char book;
	_LText();
	int size = _msize(list) / sizeof(wchar_t*);
	for (short i = 0; i < size; i++)
	{
		GotoXY(Xposition, Yposition + i);
		std::wcout << list[i];
	}
	GotoXY(Xposition, Yposition);
	std::wcout << L"> " << list[0]<<L" <";
	GotoXY(Xposition - 1, Yposition);
	short index = 0;
	while (true)
	{
		book = _getwch();
		book = toupper(book);
		if (book == 'W' || book == KEY_UP) {
			GotoXY(Xposition, Yposition + index);
			std::wcout << list[index]<<L"    ";
			if (index == 0) { index = size - 1; }
			else { index--; }
			GotoXY(Xposition, Yposition + index);
			std::wcout << L"> " << list[index]<<L" <";
			GotoXY(Xposition - 1, Yposition + index);
		}
		else if (book == 'S' || book == KEY_DOWN) {
			GotoXY(Xposition, Yposition + index);
			std::wcout << list[index] << L"    ";
			if (index == size - 1) { index = 0; }
			else { index++; }
			GotoXY(Xposition, Yposition + index);
			std::wcout << L"> " << list[index]<<L" <";
			GotoXY(Xposition - 1, Yposition + index);
		}
		else if (book == KEY_ENTER || book == ' ') {
			GotoXY(0, Yposition + size);
			_SText();
			return index;
		}
		else if (book == KEY_ESC) {
			GotoXY(0, Yposition + size);
			_SText();
			return -1;
		}
	}
}

short Menu(char** list, short Xposition, short Yposition) {
	char book;
	if (list == 0) { GotoXY(Xposition, Yposition); std::cout << ">Empty<"; _getwch(); return -1; }
	int size = _msize(list) / sizeof(char*);
	for (short i = 0; i < size; i++)
	{
		GotoXY(Xposition, Yposition + i);
		std::cout << list[i];
	}
	GotoXY(Xposition, Yposition);
	std::cout << "> " << list[0] << " <";
	GotoXY(Xposition - 1, Yposition);
	short index = 0;
	while (true)
	{
		book = _getwch();
		book = toupper(book);
		if (book == 'W' || book == KEY_UP) {
			GotoXY(Xposition, Yposition + index);
			std::cout << list[index] << "    ";
			if (index == 0) { index = size - 1; }
			else { index--; }
			GotoXY(Xposition, Yposition + index);
			std::cout << "> " << list[index] << " <";
			GotoXY(Xposition - 1, Yposition + index);
		}
		else if (book == 'S' || book == KEY_DOWN) {
			GotoXY(Xposition, Yposition + index);
			std::cout << list[index] << "    ";
			if (index == size - 1) { index = 0; }
			else { index++; }
			GotoXY(Xposition, Yposition + index);
			std::cout << "> " << list[index] << " <";
			GotoXY(Xposition - 1, Yposition + index);
		}
		else if (book == KEY_ENTER || book == ' ') {
			GotoXY(0, Yposition + size);
			return index;
		}
		else if (book == KEY_ESC) {
			GotoXY(0, Yposition + size);
			return -1;
		}
	}
}

short Choose(wchar_t** list,short X,short Y) {
	int n = _msize(list) / sizeof(wchar_t*);
	int* size = new int[n];
	int longest = 0;
	for (int i = 0; i < n; i++) {
		GotoXY(X, Y);
		size[i] = wcslen(list[i]);
		if (size[i] > longest) longest = size[i];
	}
	char book;
	_LText();
	std::wcout << list[0];
	for (int i = 0; i < longest - size[0]; i++) std::wcout << L' ';
	int index = 0;
	while(true){
		book = _getwch();
		book = toupper(book);
		if (book == 'W' || book == KEY_UP) {
			index == 0 ? index = n - 1 : index -= 1;
			GotoXY(X, Y);
			std::wcout << list[index];
			for (int i = 0; i < longest - size[index]; i++) std::wcout << L' ';
		}
		else if (book == 'S' || book == KEY_DOWN) {
			index == n - 1 ? index = 0 : index += 1;
			GotoXY(X, Y);
			std::wcout << list[index];
			for (int i = 0; i < longest - size[index]; i++) std::wcout << L' ';
		}
		else if (book == KEY_ENTER || book == ' ') {
			GotoXY(0, Y + 1);
			_SText();
			return index;
		}
		else if (book == KEY_ESC) {
			GotoXY(0, Y + 1);
			_SText();
			return index;
		}
	}
	delete[] size;//
}

short Choose(char** list, short X, short Y) {
	int n = _msize(list) / sizeof(char*);
	int* size = new int[n];
	int longest = 0;
	for (int i = 0; i < n; i++) {
		GotoXY(X, Y);
		size[i] = strlen(list[i]);
		if (size[i] > longest) longest = size[i];
	}
	char book;
	std::cout << list[0];
	for (int i = 0; i < longest - size[0]; i++) std::cout << ' ';
	int index = 0;
	while (true) {
		book = _getwch();
		book = toupper(book);
		if (book == 'W' || book == KEY_UP) {
			index == 0 ? index = n - 1 : index -= 1;
			GotoXY(X, Y);
			std::cout << list[index];
			for (int i = 0; i < longest - size[index]; i++) std::cout << ' ';
		}
		else if (book == 'S' || book == KEY_DOWN) {
			index == n - 1 ? index = 0 : index += 1;
			GotoXY(X, Y);
			std::cout << list[index];
			for (int i = 0; i < longest - size[index]; i++) std::cout << ' ';
		}
		else if (book == KEY_ENTER || book == ' ') {
			GotoXY(0, Y + 1);
			return index;
		}
		else if (book == KEY_ESC) {
			GotoXY(0, Y + 1);
			return index;
		}
	}
}

int countFile(Filelist* list) {
	Filelist* temp = list;
	int i = 0;
	do {
		i += 1;
		temp = temp->pNext;
	} while (temp != list);
	return i;
}

std::string ChoseFolder(Filelist* list, short x, short y) {
	Filelist* temp = list;
	int i = 0;
	do {
		GotoXY(x, y + i); std::cout <<temp->filename;
		i += 1;
		temp = temp->pNext;
	} while (list != temp);
	i = 0;
	int n = countFile(list) - 1;
	GotoXY(x, y); std::cout << "> " << temp->filename << " <";
	char get = 0;
	while (true)
	{
		get = _getwch();
		get = toupper(get);
		if (get == 'W' || get == KEY_UP) {
			GotoXY(x, y + i); std::cout << temp->filename << "    ";
			temp == list ? i = n : i -= 1;
			temp = temp->pPrev;
			GotoXY(x, y + i); std::cout << "> " << temp->filename << " <";
		}
		else if (get == 'S' || get == KEY_DOWN) {
			GotoXY(x, y + i); std::cout << temp->filename << "    ";
			temp == list->pPrev ? i = 0 : i += 1;
			temp = temp->pNext;
			GotoXY(x, y + i); std::cout << "> " << temp->filename << " <";
		}
		else if (get == KEY_ENTER || get == ' ') {
			return temp->filename;
		}
		else if (get == KEY_ESC) {
			return "";
		}
	}
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

Date InputDate() {
	char temp;
	std::string result = "";
	while (true)
	{
		temp = _getwch();
		if (temp == KEY_ESC) { return Date{ 00,00,0000 }; }
		if (result.size()==10 && temp == KEY_ENTER) {
			std::cout << "\n";
			break;
		}
		if (temp <= '9' && temp >= '0' && result.size()<10) {
			if (result.size() == 2 || result.size() == 5) {
				std::cout << "/" << temp;
				result.push_back(' ');
				result.push_back(temp);
			}
			else {
				std::cout << temp;
				result.push_back(temp);
			}
		}
		if (temp == KEY_BACKSPACE && result.size()>0) {
			if (result.size() == 3 || result.size() == 6)
			{
				result.pop_back();
				result.pop_back();
				std::cout << temp << temp << "  " << temp << temp;
			}
			else {
				result.pop_back();
				std::cout << temp << ' ' << temp;
			}
		}
		if ((temp=='/' || temp == ' ' || temp == '-') && (result.size()==1 || result.size()==4 )) {
			char a = result[result.size() - 1];
			result.pop_back();
			result.push_back('0');
			result.push_back(a);
			result.push_back('/');
			std::cout << char(8) << '0' << a << '/';
		}
	}
	return StringToDate(result);
}

bool LeapYear(int y)
{
	if (y % 400 == 0)
		return 1;
	else if (y % 4 == 0 && y % 25 != 0)
		return 1;
	return 0;
}

bool CheckDate(Date dat)
{
	int d = dat.dd;
	int m = dat.mm;
	int y = dat.yy;
	if (d < 1 || m < 1 || y < 0 || m > 12)
		return 0;
	if (LeapYear(y))
	{
		if (m == 2 && d > 29)
			return 0;
	}
	else
	{
		if (m == 2 && d > 28)
			return 0;
	}
	if (d > 31) return 0;
	if (d > 30)
		if (m == 4 || m == 6 || m == 9 || m == 11)
			return 0;
	return 1;
}
