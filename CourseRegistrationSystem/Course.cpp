#include"CommonFunc.h"
#include"Data.h"

Course* MakeCourse();
void FileOutCourse(_Course*, std::string);
void AddCourse(_Course*&, Course);

Course* searchCourseFile(std::string search);
_Course* searchCourse(_Course*, std::wstring&);
_Course* searchID(_Course*, std::wstring);
_Course* searchName(_Course*, std::wstring);
_Course* searchTeacher(_Course*, std::wstring);

void printCourseDay(short);
void displayCourse(_Course*);
void editCourse(_Course*&);

void displayScore(Score*);
void searchScore(_Course*);

void AddCourse(_Course*& courselist, Course* course) {
	if (courselist == nullptr) { courselist = new _Course{ course }; courselist->pNext = courselist, courselist->pPrev = courselist; return; }
	courselist->pPrev = new _Course{ course,courselist,courselist->pPrev };
	courselist->pPrev->pPrev->pNext = courselist->pPrev;
}

void FileOutCourse(_Course* cou, std::string fileout) {
	_LText();
	std::wfstream fo(fileout, std::wfstream::out);
	fo.imbue(std::locale(fo.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	_Course* temp = cou;
	fo << wchar_t(0xfeff);
	do
	{
		fo << cou->course->ID << L',' << cou->course->name << L',' << cou->course->teacher << L',' << cou->course->credit << L',' << cou->course->performed[0].day << L',';
		fo << cou->course->performed[0].session << L',' << cou->course->performed[1].day << L',' << cou->course->performed[1].session << L'\n';
		cou = cou->pNext;
	} while (cou != temp);
	fo.close();
	_SText();
}

Course* MakeCourse() {
	Course* result = new Course;
	
	std::string stemp;
	std::cout << "Course ID: ";
	std::getline(std::cin, stemp);
	int size = stemp.length();
	result->ID = new char[size + 1];
	result->ID[size] = '\0';
	stemp.copy(result->ID, size);

	_LText();
	std::wcout << "Course name: ";
	std::wstring temp;
	std::getline(std::wcin, temp);
	size = temp.length();
	result->name = new wchar_t[size + 1];
	result->name[size] = L'\0';
	temp.copy(result->name, size);

	std::wcout << "Teacher name: ";
	std::getline(std::wcin, temp);
	size = temp.length();
	result->teacher = new wchar_t[size + 1];
	result->teacher[size] = L'\0';
	temp.copy(result->teacher, size);
	_SText();

	std::cout << "Number of credits: ";
	std::cin >> result->credit;
	std::cin.ignore(1000, '\n');

	std::cout << "Schedule \n";// hmm not workking

	char** day = new char* [7];
	char** ses = new char* [4];
	day[0] = new char[]{ "MONDAY" };
	day[1] = new char[]{ "TUESDAY" };
	day[2] = new char[]{ "WEDNESDAY" };
	day[3] = new char[]{ "THURSDAY" };
	day[4] = new char[]{ "FRIDAY" };
	day[5] = new char[]{ "SATURDAY" };
	day[6] = new char[]{ "SUNDAY" };

	ses[0] = new char[]{ "S1 (07:30)" };
	ses[1] = new char[]{ "S2 (09:30)" };
	ses[2] = new char[]{ "S3 (13:30)" };
	ses[3] = new char[]{ "S4 (15:30)" };

	for (int i = 0; i < 2; i++) {
		GotoXY(10, 4 + i);
		std::cout << "Day: ";
		result->performed[i].day = Choose(day, 15, 4 + i);
		GotoXY(26, 4 + i);
		std::cout << "Ses: ";
		result->performed[i].session = Choose(ses, 30, 4 + i);
	}
	DealocatedArrString(ses);
	DealocatedArrString(day);
	return result;
}
void MakeCourse(std::string current) {
	system("cls");
	char** menu=new char*[2];
	_Course* cou = nullptr;
	menu[0] = new char[] {"Add Course"};
	menu[1] = new char[] {"Done"};
	int check = Menu(menu, 5, 2);
	while (check==0)
	{
		system("cls");
		AddCourse(cou, MakeCourse());
		system("cls");
		check = Menu(menu, 5, 2);
	}
	std::cout << "Saving.... ";
	CourseToBin(cou, current);
	std::cout << "\n> done <";
	_getwch();
	//delete cou here;
}
_Course* searchID(_Course* courselist, std::wstring search) {
	int size = strlen(courselist->course->ID);
	wchar_t* t = new wchar_t[size];
	StrToLStr(t, size, courselist->course->ID);
	if (wcscmp(t, StrToChar(search)) == 0) {
		delete[]t;
		return courselist;
	}
	delete[]t;

	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		size = strlen(courselist->course->ID);
		t = new wchar_t[size];
		StrToLStr(t, size, courselist->course->ID);
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
	if (wcscmp(courselist->course->name, StrToChar(search)) == 0) return courselist;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course->name, StrToChar(search)) == 0) return courselist;
		courselist = courselist->pNext;
	}
	return nullptr;
}

_Course* searchTeacher(_Course* courselist, std::wstring search) {
	if (wcscmp(courselist->course->teacher, StrToChar(search)) == 0) return courselist;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course->teacher, StrToChar(search)) == 0) return courselist;
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
	_SText();
}

void displayCourse(Course* cou) {
	std::cout << "ID: " << cou->ID << "\n";
	_LText();
	std::wcout << "Name: " << cou->name << "\n";
	std::wcout << "Teacher: " << cou->teacher << "\n";
	_SText();
	std::cout << "Credits: " << cou->credit << "\n";
	std::cout << "Number of students: " << cou->numberofstudent << "/" << cou->maxstudent << "\n";
	std::cout << "Schedule:\n";
	for (int i = 0; i < 2; i++) {
		std::cout << "   Day: "; printCourseDay(cou->performed[i].day);
		std::cout << "   Session: S" << cou->performed[i].session + 1 << "\n";
	}
	std::cout << '\n';
}
void displayCourse(Course** cou) {
	int n = _msize(cou) / sizeof(cou);
	std::cout << std::setw(10) << "ID" << std::setw(15) << "Course Name" << std::setw(15) << "Teacher" << std::setw(15) << "Student" << std::setw(30) << "Schedule";
	for (int i = 0; i < n; i++) {
		std::cout << cou[i]->ID;
		_LText();
		std::wcout << cou[i]->name << std::setw(20) << cou[i]->teacher;
		_SText();
		std::cout << std::setw(10) << cou[i]->numberofstudent << "/" << cou[i]->maxstudent << std::setw(10);

	}
}

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

	if (cou->course->score == nullptr) {
		std::wcout << "No score available\n";
	}
	else if (id == cou->course->score->ID) {
		std::wcout << "\n";
		displayScore(cou->course->score);
	}
	else {
		Score* first = cou->course->score;
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
Date TakeDateEnd(std::string current) {
	int sem = current.find('\\', 0);
	sem = current.find('\\', sem + 1);
	int temp = current.find('\\', sem + 1);
	char* year = new char[temp - sem];
	current.copy(year, temp - sem, sem + 1);
	year[temp - sem - 1] = '\0';
	sem = current[current.size() - 1] - '0';

	std::fstream fi("Data\\SchoolYear\\" + ToString(year) + "\\time", std::fstream::in | std::fstream::binary);
	Date check;
	for (int i = 0; i < sem; i++) {
		fi.read((char*)&check, sizeof(Date));
		fi.read((char*)&check, sizeof(Date));
	}
	delete[] year;
	return check;
}
void editCourse(Course* cour, std::string filename, std::string current) {
	Date check = TakeDateEnd(current);
	system("cls");
	std::cout << check;
	std::cout << "-------- Edit course --------";
	if (check < GetTime()) {
		char** menu = new char* [6];
		menu[0] = new char[] {"Teacher"};
		menu[1] = new char[] {"Max Student"};
		menu[2] = new char[] {"Performed"};
		menu[0] = new char[] {"Back"};
		int chose = -1;
		_getwch();
	}
	else {
		char** menu = new char* [6];
		menu[0] = new char[] {"Teacher"};
		menu[3] = new char[] {"Score"};
		menu[0] = new char[] {"Back"};
		int chose = -1;
	}
}

void deleteCourse(Course* cour, std::string filename, std::string current) {

}



void editCourse(std::string filename,std::string current) {
	system("cls");
	std::cout << "-------- Edit Course ----------\n";
	Course* cour = BinToCourse(current + "\\" + filename);
	displayCourse(cour);
	char** menu = new char* [3];
	menu[0] = new char[] {"Edit"};
	menu[1] = new char[] {"Delete (Only before register time) "};
	menu[2] = new char[] {"back"};
	int chose = Menu(menu, 5, 10);
	DealocatedArrString(menu);
	switch (chose)
	{
	case 0: editCourse(cour,filename,current); break;
	case 1: deleteCourse(cour,filename,current); break;
	}
}

Course* searchCourseFile(std::string search ) {
	char year[5];
	year[4] = '\0';
	int size = search.length();
	int n = size - 5;
	for (int i = 0; i < 4; i++) {
		year[i] = search[n + i];
	}
	char* local = new char[] {"Data\\Grade\\K"};
	char* temp = StrCat(year, "\\Semester" + search[size - 1]);
	char* temp1 = StrCat(temp, "\\");
	delete[]temp;
	StrCat(temp1, size - 5, search);
	char* direction = StrCat(local, temp1);
	Course* cou = BinToCourse(direction);
	if (cou == nullptr) std::cout << "Unable to find " << search << "\n";
	delete[]temp1, direction, local;
	return cou;
}
