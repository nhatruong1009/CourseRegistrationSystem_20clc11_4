#include"NewStructs.h"
#include"DataControl.h"
#include <fstream>
#include <wchar.h>
#include <io.h>
#include <fcntl.h>
#include <string>
#include <windows.h>
#include<ctime>
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

bool isLoggedIn() {
	std::wstring username, password, un, pw;
	std::wcout << "Enter username: ";
	std::wcin >> username;
	std::wcout << "Enter password: ";
	std::wcin >> password;
	std::wifstream read("testLogIn\\testLogIn.txt");
	std::getline(read, un);
	std::getline(read, pw);
	if (un == username && pw == password) return true;
	return false;
}
int main() {

	VietNamText();

	int choice;
	std::wcout << "1: Login\nYour choice: "; std::wcin >> choice;
	if (choice == 1) {
		if (!isLoggedIn()) {
			std::wcout<<"Failed";
		}
		else std::wcout << "Successful";
	}


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
}
