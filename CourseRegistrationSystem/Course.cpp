#include"CommonFunc.h"
#include"Data.h"

Course MakeCourse() {
	Course result;
	_LText();
	std::wcout << "Course name: ";
	std::wstring temp;
	std::getline(std::wcin, temp);
	int size = temp.length();
	result.name = new wchar_t[size + 1];
	result.name[size] = L'\0';
	temp.copy(result.name, size);

	std::wcout << "Course ID: ";
	std::getline(std::wcin, temp);
	size = temp.length();
	result.ID = new char[size + 1];
	result.ID[size] = '\0';
	LStrToStr(result.ID, size, temp);

	std::wcout << "Teacher name: ";
	std::getline(std::wcin, temp);
	size = temp.length();
	result.teacher = new wchar_t[size + 1];
	result.teacher[size] = L'\0';
	temp.copy(result.teacher, size);

	std::wcout << "Number of credits: ";
	std::wcin >> result.credit;
	std::wcin.ignore(1000, L'\n');

	std::wcout << "Schedule (ex. MON,S1) \n";// hmm not workking

	wchar_t** day = new wchar_t* [7];
	wchar_t**ses = new wchar_t* [4];
	day[0] = new wchar_t[4]{ L"MON" };
	day[1] = new wchar_t[4]{ L"TUE" };
	day[2] = new wchar_t[4]{ L"WED" };
	day[3] = new wchar_t[4]{ L"THU" };
	day[4] = new wchar_t[4]{ L"FRI" };
	day[5] = new wchar_t[4]{ L"SAT" };
	day[6] = new wchar_t[4]{ L"SUN" };

	ses[0] = new wchar_t[3]{ L"S1" };
	ses[1] = new wchar_t[3]{ L"S2" };
	ses[2] = new wchar_t[3]{ L"S3" };
	ses[3] = new wchar_t[3]{ L"S4" };

	for (int i = 0; i < 2; i++) {
		GotoXY(10, 10 + i);
		std::wcout << "Day: ";
		result.performed[i].day = Choose(day, 15, 10 + i);
		GotoXY(20, 10 + i);
		std::wcout << "Ses: ";
		result.performed[i].session = Choose(ses, 25, 10 + i);
	}
	for (int i = 0; i < 4; i++) {
		delete[] day[i],ses[i];
	}
	for (int i = 4; i < 7; i++) {
		delete[] day[i];
	}
	delete[] day, ses;
	_SText();
	return result;
}
