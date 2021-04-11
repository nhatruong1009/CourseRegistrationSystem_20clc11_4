#include"CommonFunc.h"
#include"Data.h"

Course MakeCourse() {
	Course result;
	std::cout << "Course name: ";
	std::string temp;
	std::getline(std::cin, temp);
	int size = temp.length();
	result.name = new wchar_t[size + 1];
	result.name[size] = L'\0';
	StrToLStr(result.name, size, temp);  //Not working??

	std::cout << "Course ID: ";
	std::getline(std::cin, temp);
	size = temp.length();
	result.ID = new char[size + 1];
	result.ID[size] = '\0';
	for (int i = 0; i < size; i++) {
		result.ID[i] = temp[i];
	}

	std::cout << "Teacher name: ";
	std::getline(std::cin, temp);
	size = temp.length();
	result.teacher = new wchar_t[size + 1];
	result.teacher[size] = L'\0';
	StrToLStr(result.teacher, size, temp); //Not working??

	std::cout << "Number of credits: ";
	std::cin >> result.credit;

	std::cout << "Schedule (ex. MON,S1) \n";
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
