#include"CommonFunc.h"
#include"Data.h"

//---17/04/2021
Course StringToCourse(std::wstring str) {
	//ID, Course name, Teacher, Credits, Dates, Sessions
	Course cou;
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	_LText();

	cou.ID = new char[end - beg + 1];
	cou.ID[end - beg] = L'\0';
	LStrToStr(cou.ID, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	cou.name = new wchar_t[end - beg + 1];
	cou.name[end - beg] = L'\0';
	str.copy(cou.name, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	cou.teacher = new wchar_t[end - beg + 1];
	cou.teacher[end - beg] = L'\0';
	str.copy(cou.teacher, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou.credit = StringToInt(temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou.performed[0].day[3] = L'\0';
	LStrToStr(cou.ID, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou.performed[0].session[2] = L'\0';
	LStrToStr(cou.ID, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou.performed[1].day[3] = L'\0';
	LStrToStr(cou.ID, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou.performed[1].session[2] = L'\0';
	LStrToStr(cou.ID, end - beg, temp);
	delete[] temp;

	return cou;
}

void AddCourse(_Course*& courselist, Course course) {
	if (courselist == nullptr) { courselist = new _Course{ course }; courselist->pNext = courselist, courselist->pPrev = courselist; return; }
	courselist->pPrev = new _Course{ course,courselist,courselist->pPrev };
	courselist->pPrev->pPrev->pNext = courselist->pPrev;
}

_Course* FileInCourse(std::string filename) {
	_LText();
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	_Course* allCourse = nullptr;
	std::wstring temp;
	while (fi)
	{
		std::getline(fi, temp);
		if (temp.length() != 0) AddCourse(allCourse, StringToCourse(temp));
	}
	_SText();
	return allCourse;
}

void FileOutCourse(_Course* cou, std::string fileout) {
	_LText();
	std::wfstream fo(fileout, std::wfstream::out);
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Course* temp = cou;
	fo << wchar_t(0xfeff);
	do
	{
		fo << cou->course.ID << L',' << cou->course.name << L',' << cou->course.teacher << L',' << cou->course.credit << L',' << cou->course.performed[0].day << L',';
		fo << cou->course.performed[0].session << L',' << cou->course.performed[1].day << L',' << cou->course.performed[1].session << L'\n';
		cou = cou->pNext;
	} while (cou != temp);
	fo.close();
	_SText();
}
//--------

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
	DealocatedArrString(ses);
	DealocatedArrString(day);
	_SText();
	return result;
}
