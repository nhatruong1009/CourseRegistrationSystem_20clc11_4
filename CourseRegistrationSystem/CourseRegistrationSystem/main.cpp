#include"NewStructs.h"
#include"DataControl.h"
#include <fstream>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <windows.h>
void VietNamText()
{
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);
	HANDLE hdlConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX consoleFont;
	consoleFont.cbSize = sizeof(consoleFont);
	GetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
	memcpy(consoleFont.FaceName, L"Consolas", sizeof(consoleFont.FaceName));
	SetCurrentConsoleFontEx(hdlConsole, FALSE, &consoleFont);
}

int main() {
	VietNamText();
	std::wstring file;
	std::wcin >> file;
	_Student* in = AddStudent(file);
	PrintStu(in);
	std::wcin >> file;
	SaveStudent(in, file);
	std::wcout << '\n';
	std::wcin >> file;
	_Student* a = LoadStudent(file);
	PrintStu(a);
	std::wcout <<int( a->student.firstname[0])<<" ";
}
