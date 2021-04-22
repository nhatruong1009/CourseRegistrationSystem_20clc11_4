#include"CommonFunc.h"
#include"Data.h"

Course MakeCourse();
void FileOutCourse(_Course*, std::string);
void AddCourse(_Course*&, Course);


Course* searchCourseFile();
_Course* searchCourse(_Course*, std::wstring&);
_Course* searchID(_Course*, std::wstring);
_Course* searchName(_Course*, std::wstring);
_Course* searchTeacher(_Course*, std::wstring);

void printCourseDay(short);
void displayCourse(_Course*);
void editCourse(_Course*&);

void displayScore(Score*);
void searchScore(_Course*);




	//---17/04/2021
	// //fix latter
	//Course StringToCourse(std::wstring str) {
	//	//ID, Course name, Teacher, Credits, Dates, Sessions
	//	Course cou;
	//	wchar_t* temp = nullptr;
	//	int beg = str.find(L',', 0) + 1;
	//	int end = str.find(L',', beg);
	//
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	_LText();
	//
	//	cou.ID = new char[end - beg + 1];
	//	cou.ID[end - beg] = L'\0';
	//	LStrToStr(cou.ID, end - beg, temp);
	//	delete[] temp;
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	cou.name = new wchar_t[end - beg + 1];
	//	cou.name[end - beg] = L'\0';
	//	str.copy(cou.name, end - beg, beg);
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	cou.teacher = new wchar_t[end - beg + 1];
	//	cou.teacher[end - beg] = L'\0';
	//	str.copy(cou.teacher, end - beg, beg);
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	cou.credit = StringToInt(temp);
	//	delete[] temp;
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	cou.performed[0].day[3] = L'\0';
	//	LStrToStr(cou.ID, end - beg, temp);
	//	delete[] temp;
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	cou.performed[0].session[2] = L'\0';
	//	LStrToStr(cou.ID, end - beg, temp);
	//	delete[] temp;
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	cou.performed[1].day[3] = L'\0';
	//	LStrToStr(cou.ID, end - beg, temp);
	//	delete[] temp;
	//
	//	beg = end + 1;
	//	end = str.find(L',', beg);
	//	temp = new wchar_t[end - beg + 1];
	//	temp[end - beg] = L'\0';
	//	str.copy(temp, end - beg, beg);
	//	cou.performed[1].session[2] = L'\0';
	//	LStrToStr(cou.ID, end - beg, temp);
	//	delete[] temp;
	//
	//	return cou;
	//}

void AddCourse(_Course*& courselist, Course course) {
	if (courselist == nullptr) { courselist = new _Course{ course }; courselist->pNext = courselist, courselist->pPrev = courselist; return; }
	courselist->pPrev = new _Course{ course,courselist,courselist->pPrev };
	courselist->pPrev->pPrev->pNext = courselist->pPrev;
}

	//_Course* FileInCourse(std::string filename) {
	//	_LText();
	//	std::wfstream fi(filename, std::wfstream::in);
	//	if (!fi) { return nullptr; }
	//	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	//	_Course* allCourse = nullptr;
	//	std::wstring temp;
	//	while (fi)
	//	{
	//		std::getline(fi, temp);
	//		if (temp.length() != 0) AddCourse(allCourse, StringToCourse(temp));
	//	}
	//	_SText();
	//	return allCourse;
	//}

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
	wchar_t** ses = new wchar_t* [4];
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

_Course* searchID(_Course* courselist, std::wstring search) {
	int size = strlen(courselist->course.ID);
	wchar_t* t = new wchar_t[size];
	StrToLStr(t, size, courselist->course.ID);
	if (wcscmp(t, StrToChar(search)) == 0) {
		delete[]t;
		return courselist;
	}
	delete[]t;

	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		size = strlen(courselist->course.ID);
		t = new wchar_t[size];
		StrToLStr(t, size, courselist->course.ID);
		if (wcscmp(t, StrToChar(search)) == 0) {
			delete[]t;
			return courselist;
		}
		delete[]t;
		courselist = courselist->pNext;
	}
	return nullptr;
}

_Course* searchName(_Course* courselist, std::wstring search) {
	if (wcscmp(courselist->course.name, StrToChar(search)) == 0) return courselist;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course.name, StrToChar(search)) == 0) return courselist;
		courselist = courselist->pNext;
	}
	return nullptr;
}

_Course* searchTeacher(_Course* courselist, std::wstring search) {
	if (wcscmp(courselist->course.teacher, StrToChar(search)) == 0) return courselist;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course.teacher, StrToChar(search)) == 0) return courselist;
		courselist = courselist->pNext;
	}
	return nullptr;
}

_Course* searchCourse(_Course* courselist, std::wstring& search) {
	_Course* result = nullptr;
	char book;
	_LText();
	std::wcout << "Search options:\n";
	std::wcout << "1. Search by ID\n2. Search by Name\n3. Search by Teacher\n0. Cancel\n\n";
	book = _getwch();
	while (book < '0' || book > '3') book = _getwch();
	if (book == '0') {
		_SText();
		return nullptr;
	}
	std::wcout << "Search: ";
	std::getline(std::wcin, search);
	switch (book) {
	case '1':
		result = searchID(courselist, search);
		break;
	case '2':
		result = searchName(courselist, search);
		break;
	case '3':
		result = searchTeacher(courselist, search);
		break;
	}
	_SText();
	return result;
}

void printCourseDay(short a) {
	_LText();
	switch (a) {
	case 0:
		std::wcout << std::setw(10) << std::left << "Monday";
		break;
	case 1:
		std::wcout << std::setw(10) << std::left << "Tuesday";
		break;
	case 2:
		std::wcout << std::setw(10) << std::left << "Wednesday";
		break;
	case 3:
		std::wcout << std::setw(10) << std::left << "Thursday";
		break;
	case 4:
		std::wcout << std::setw(10) << std::left << "Friday";
		break;
	case 5:
		std::wcout << std::setw(10) << std::left << "Saturday";
		break;
	case 6:
		std::wcout << std::setw(10) << std::left << "Sunday";
		break;
	}
}

void displayCourse(_Course* cou) {
	_LText();
	std::wcout << "1. Name: " << cou->course.name << "\n";
	std::wcout << "2. ID: " << cou->course.ID << "\n";
	std::wcout << "3. Teacher: " << cou->course.teacher << "\n";
	std::wcout << "4. Credits: " << cou->course.credit << "\n";
	std::wcout << "5. Number of students: " << cou->course.numberofstudent << "/" << cou->course.maxstudent << "\n";
	std::wcout << "6. Schedule:\n";
	for (int i = 0; i < 2; i++) {
		std::wcout << "   Day: "; printCourseDay(cou->course.performed[i].day);
		std::wcout << "   Session: S" << cou->course.performed[i].session + 1 << "\n";
	}
	_SText();
}

//void editCourse(_Course*& cou) {
//	char book;
//	int size;
//	std::wstring temp;
//	_LText();
//	std::wcout << "Edit Course\n\n\n";
//	displayCourse(cou);
//	std::wcout << "\n" << std::setw(12) << "0. Done.\n";
//	while (1) {
//		book = _getwch();
//		while (book < '0' || book > '6') book = _getwch();
//		if (book == '0') {
//			_SText();
//			return;
//		}
//		switch (book) {
//		case '1':
//			for (int i = 0; i < 3; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 35; j++) std::wcout << L" ";
//			}
//			GotoXY(10, 10);
//			std::wcout << "Course name: ";
//			std::getline(std::wcin, temp);
//			int size = temp.length();
//			delete[]cou->course.name;
//			cou->course.name = new wchar_t[size + 1];
//			cou->course.name[size] = L'\0';
//			temp.copy(cou->course.name, size);
//			break;
//
//		case '2':
//			for (int i = 0; i < 3; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 35; j++) std::wcout << L" ";
//			}
//			GotoXY(10, 10);
//			std::wcout << "Course ID: ";
//			std::getline(std::wcin, temp);
//			size = temp.length();
//			delete[]cou->course.ID;
//			cou->course.ID = new char[size + 1];
//			cou->course.ID[size] = '\0';
//			LStrToStr(cou->course.ID, size, temp);
//			break;
//
//		case'3':
//			for (int i = 0; i < 3; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 20; j++) std::wcout << L" ";
//			}
//			GotoXY(10, 10);
//			std::wcout << "Teacher name: ";
//			std::getline(std::wcin, temp);
//			size = temp.length();
//			delete[]cou->course.teacher;
//			cou->course.teacher = new wchar_t[size + 1];
//			cou->course.teacher[size] = L'\0';
//			temp.copy(cou->course.teacher, size);
//			break;
//
//		case '4':
//			for (int i = 0; i < 3; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 15; j++) std::wcout << L" ";
//			}
//			GotoXY(10, 10);
//			std::wcout << "Number of credits: ";
//			std::wcin >> cou->course.credit;
//			std::wcin.ignore(1000, L'\n');
//			break;
//
//		case '5':
//			for (int i = 0; i < 3; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 15; j++) std::wcout << L" ";
//			}
//			GotoXY(10, 10);
//			std::wcout << "Unchangable";
//			break;
//
//		case '6':
//			wchar_t** day = new wchar_t* [7];
//			wchar_t** ses = new wchar_t* [4];
//			day[0] = new wchar_t[4]{ L"MON" };
//			day[1] = new wchar_t[4]{ L"TUE" };
//			day[2] = new wchar_t[4]{ L"WED" };
//			day[3] = new wchar_t[4]{ L"THU" };
//			day[4] = new wchar_t[4]{ L"FRI" };
//			day[5] = new wchar_t[4]{ L"SAT" };
//			day[6] = new wchar_t[4]{ L"SUN" };
//
//			ses[0] = new wchar_t[3]{ L"S1" };
//			ses[1] = new wchar_t[3]{ L"S2" };
//			ses[2] = new wchar_t[3]{ L"S3" };
//			ses[3] = new wchar_t[3]{ L"S4" };
//			for (int i = 0; i < 4; i++) {
//				GotoXY(7, 9 + i);
//				for (int j = 0; j < 35; j++) std::wcout << L" ";
//			}
//			for (int i = 0; i < 2; i++) {
//				GotoXY(10, 10 + i);
//				std::wcout << "Day: ";
//				cou->course.performed[i].day = Choose(day, 15, 10 + i);
//				GotoXY(20, 10 + i);
//				std::wcout << "Ses: ";
//				cou->course.performed[i].session = Choose(ses, 25, 10 + i);
//			}
//			DealocatedArrString(ses);
//			DealocatedArrString(day);
//			break;
//		}
//		system("cls");
//		displayCourse(cou);
//	}
//	_SText();
//}

void displayScore(Score* a) {
	_LText();
	std::wcout << "Name: " << a->name;
	std::wcout << "\nID: " << a->ID;
	std::wcout << "\nScore: ";
	std::wcout << "\nMid term: " << a->mids;
	std::wcout << "   Final: " << a->finals;
	std::wcout << "   Others: " << a->others;
	std::wcout << "\nTotal: " << a->totals;
	_SText();
}

void searchScore(_Course* allcourse) {
	_LText();
	unsigned int id;
	std::wstring search;
	_Course* cou = searchCourse(allcourse, search);
	system("cls");
	std::wcout << "Course: " << search << "\n";
	std::wcout << "Student ID: ";
	std::wcin >> id;
	std::wcin.ignore(1000, L'\n');

	if (cou->course.score == nullptr) {
		std::wcout << "No score available\n";
	}
	else if (id == cou->course.score->ID) {
		std::wcout << "\n";
		displayScore(cou->course.score);
	}
	else {
		Score* first = cou->course.score;
		Score* cur = first->pNext;
		while (cur != first) {
			if (id == cur->ID) break;
			cur = cur->pNext;
		}
		if (cur != first) displayScore(cur);
		else std::wcout << "Unable to find student\n";
	}
	_SText();
}
	

Course* searchCourseFile() {
	std::string search;
	std::cout << "Search: ";
	std::cin >> search;
	char year[5];
	year[4] = '\0';
	int size = search.length();
	int n = size - 5;
	for (int i = 0; i < 4; i++) {
		year[i] = search[n + i];
	}
	char* local = new char[] {"Data\\Grade\\K"};
	char* temp = StrCat(year, "\\Semester" + search[size - 1]);
	char* direction = StrCat(local, temp);
	Course* cou = BinToCourse(direction);
	if (cou == nullptr) std::cout << "Unable to find " << search << "\n";
	return cou;
}
