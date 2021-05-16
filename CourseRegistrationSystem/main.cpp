#include"Data.h"
#include"Sup.h"
#include"Interface.h"
#include"Staff.h"

void main(){
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	{
		std::string current = "";
		fistrun(current);
		secondrun();
		userTypeMode();
	}
	if (_CrtDumpMemoryLeaks())
	{
		std::cout << "Leak";
	}
	else std::cout << "No";
}