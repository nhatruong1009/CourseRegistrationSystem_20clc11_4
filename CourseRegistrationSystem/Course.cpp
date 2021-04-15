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
	_SText();

	std::cout << "Schedule (ex. MON,S1) \n";// hmm not workking
	for (int i = 0; i < 2; i++) {
		std::cout << "Day: ";
		std::cin >> result.performed[i].day;
		result.performed[i].day[3] = '\0';

		std::cout << "Session: ";
		std::cin >> result.performed[i].session;
		result.performed[i].session[2] = '\0';
	}
	return result;
}
