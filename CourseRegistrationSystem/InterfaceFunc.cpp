#include"Interface.h"

//********** SUPFUNCTION ********
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
inline void removereg(Course** reg, Course* re) {
	int n = 0;
	for (int i = 0; i < 5; i++) {
		if (reg[i] == re) {
			n = i;
			break;
		}
	}
	for (int i = n; i < 4; i++) {
		reg[i] = reg[i + 1];
	}
	reg[4] = nullptr;
}


//*******************************

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
	std::wcout << L"> " << list[0] << L" <";
	GotoXY(Xposition - 1, Yposition);
	short index = 0;
	while (true)
	{
		book = _getwch();
		book = toupper(book);
		if (book == 'W' || book == KEY_UP) {
			GotoXY(Xposition, Yposition + index);
			std::wcout << list[index] << L"    ";
			if (index == 0) { index = size - 1; }
			else { index--; }
			GotoXY(Xposition, Yposition + index);
			std::wcout << L"> " << list[index] << L" <";
			GotoXY(Xposition - 1, Yposition + index);
		}
		else if (book == 'S' || book == KEY_DOWN) {
			GotoXY(Xposition, Yposition + index);
			std::wcout << list[index] << L"    ";
			if (index == size - 1) { index = 0; }
			else { index++; }
			GotoXY(Xposition, Yposition + index);
			std::wcout << L"> " << list[index] << L" <";
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
short Choose(wchar_t** list, short X, short Y) {
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
	while (true) {
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
			//_SText();
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
void pickSchedule(Course* cou, int x, int y) {
	char** day = new char* [7];
	char** ses = new char* [4];
	day[0] = new char[] { "MONDAY" };
	day[1] = new char[] { "TUESDAY" };
	day[2] = new char[] { "WEDNESDAY" };
	day[3] = new char[] { "THURSDAY" };
	day[4] = new char[] { "FRIDAY" };
	day[5] = new char[] { "SATURDAY" };
	day[6] = new char[] { "SUNDAY" };

	ses[0] = new char[] { "S1 (07:30)" };
	ses[1] = new char[] { "S2 (09:30)" };
	ses[2] = new char[] { "S3 (13:30)" };
	ses[3] = new char[] { "S4 (15:30)" };

	for (int i = 0; i < 2; i++) {
		GotoXY(x, y + i);
		std::cout << "Day: ";
		cou->performed[i].day = Choose(day, x + 5, y + i);
		GotoXY(x + 16, y + i);
		std::cout << "Ses: ";
		cou->performed[i].session = Choose(ses, x + 16 + 5, y + i);
	}
	DealocatedArrString(ses);
	DealocatedArrString(day);
}

void PrintStu(Student* a) {
	if (a == nullptr) return;
	_LText();
	std::wcout << a->ID << '\t';
	std::wcout << std::setw(25) << std::left << a->firstname << std::setw(10);
	std::wcout << a->lastname << '\t' << std::setw(11);
	if (a->gender == 'M' || a->gender == 'N') std::wcout << "Men";
	else std::wcout << "Women";
	std::wcout << std::left << a->birth << std::setw(15);
	std::wcout << std::right << a->SocialID << '\n';
	_SText();
}
void PrintStu(_Student* stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID\n";
	do
	{
		PrintStu(stu->student);
		stu = stu->pNext;
	} while (stu != temp);
}
void PrintStu(Student** stu, int c) {
	if (stu == nullptr) return;
	system("cls");
	int n = _msize(stu) / sizeof(stu);
	int cur = c;
	char u;
	std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
	do {
		GotoXY(0, 1);
		for (int i = c - cur; i < c && i < n; i++) {
			PrintStu(stu[i]);
		}
		u = toupper(_getwch());
		if (u == 'A' || u == KEY_LEFT) {
			if (c != cur) {
				c -= cur;
				system("cls");
				std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
			}
		}
		if (u == 'D' || u == KEY_RIGHT) {
			if (c < n) {
				c += cur;
				system("cls");
				std::cout << std::setw(5) << "ID" << std::setw(25) << "Fist Name" << std::setw(20) << "Last name" << std::setw(10) << "Gender" << std::setw(12) << "Birth" << std::setw(20) << "Social ID";
			}
		}
	} while (u != KEY_ENTER);
}

void displayCourse(Course* cou) {
	std::cout << "   ID: " << cou->ID << "\n";
	_LText();
	std::wcout << "   Name: " << cou->name << "\n";
	std::wcout << "   Teacher: " << cou->teacher << "\n";
	_SText();
	std::cout << "   Credits: " << cou->credit << "\n";
	std::cout << "   Number of students: " << std::setw(2) << cou->numberofstudent << "/" << cou->maxstudent << "\n";
	std::cout << "   Schedule:\n";
	for (int i = 0; i < 2; i++) {
		std::cout << "      Day: "; printCourseDay(cou->performed[i].day);
		std::cout << "      Session: S" << cou->performed[i].session + 1 << "\n";
	}
	std::cout << "------------------------\n";
}
void displayCourse(Course** cou) {
	int n = _msize(cou) / sizeof(cou);
	std::cout << std::setw(10) << "ID" << std::setw(15) << "Course Name" << std::setw(15) << "Teacher" << std::setw(15) << "Student" << std::setw(30) << "Schedule";
	for (int i = 0; i < n; i++) {
		displaylistCourse(cou[i]);
		std::cout << '\n';
	}
}
void displaylistCourse(Course* cou) {
	std::cout << cou->ID << '\t';
	_LText();
	std::wcout << cou->name << '\t' << cou->teacher;
	_SText();
	std::cout << '\t' << cou->numberofstudent << "/" << cou->maxstudent << "\t";
	for (int i = 0; i < 2; i++) {
		printCourseDay(cou->performed[i].day);
		std::cout << "  S" << cou->performed[i].session + 1 << "  ";
	}
}

void inline updateSemesterResult(std::string sem) {// this really hard :(( i hope it work
	Filelist* Courses = TakeFileInFolder(sem);
	int n = CountFile(Courses);
	for (int i = 0; i < n; i++) {
		if (Courses->filename.length() > 5 && Courses->filename.compare(Courses->filename.length() - 5, 5, "Score") == 0) { DeleteCurFileList(Courses); i -= 1; n -= 1; }
		else Courses = Courses->pNext;
	}

	for (int i = 0; i < n; i++) { // ok, time to update :<
		Course* temp = BinToCourse(sem + "\\" + Courses->filename);
		for (int j = 0; j < temp->numberofstudent; j++) {
			Student* stu = BinToStu(GetFilePath(temp->stuID[j]));

			//take the idCourse to the last
			int m = _msize(stu->coursenow) / sizeof(stu->coursenow);
			for (int i = 0; i < m; i++) {
				if (strncmp(stu->coursenow[i], temp->ID, sizeof(temp->ID)) == 0) {
					char* swap = stu->coursenow[i];
					stu->coursenow[i] = stu->coursenow[m - 1];
					stu->coursenow[m - 1] = swap;
					break;
				}
			}
			m -= 1;

			Score score = GetStuScore(sem + "\\" + Courses->filename + "Score", stu->ID);
			if(score.name!=nullptr) delete[] score.name;// btw it not neccessary
			int n = 0;
			if (stu->allcourse != nullptr) n = _msize(stu->allcourse) / sizeof(stu->allcourse);
			n += 1;
			//just keep;
			char** his = stu->allcourse;
			stu->allcourse = new char* [n];
			for (int i = 0; i < n - 1; i++) {
				stu->allcourse[i] = his[i];
			}
			stu->allcourse[n - 1] = stu->coursenow[m];

			delete[] his; //detele the poiter point to data, not the data
			his = stu->coursenow;
			stu->coursenow = nullptr;
			if (m > 0) stu->coursenow = new char* [m];
			for (int i = 0; i < m; i++) {
				stu->coursenow[i] = his[i];
			}
			delete[] his;

			//update Score :((
			stu->GPA = ((stu->GPA * (float(n) - 1)) + score.totals) / float(n); // Old GPA*number of olD Subject + this Course score and / for numberof subect
			StuToBin(stu, GetFilePath(stu->ID));
			deleteStu(stu);
		}
		deleteCourse(temp);
		Courses = Courses->pNext;
	}
}
std::string secondrun() {
	std::fstream file("currentsem", std::fstream::in|std::fstream::binary);
	if (!file) return "";// not in time of any semester
	int year, sem;
	file.read((char*)&year, sizeof(int));
	file.read((char*)&sem, sizeof(int));
	Date start, end;
	file.close();
	file.open("Data\\SchoolYear\\" + std::to_string(year) + "\\time", std::fstream::in | std::fstream::binary);
	for (int i = 0; i < sem; i++) {
		file.read((char*)&start, sizeof(Date));
		file.read((char*)&end, sizeof(Date));
	}
	if (GetTime() < start) return "";// not in time so can't do anything
	if (GetTime() > end) {
		// load all student and update them score;
		updateSemesterResult("Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem));

		_wremove(L"currentsem");
		return "done"; // this end of semester so remove file, file not exits now so it can't change anything too;
	}
	return "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
	// can change score and somthing just like this of any thing of Course
}
int fistrun(std::string& current) {
	std::fstream file("firstrun", std::fstream::in | std::ios::binary);
	if (!file) return -1;// everything done for this semester
	int year;
	int sem;
	Date Start;
	Date End;
	file.read((char*)&year, sizeof(int));
	file.read((char*)&sem, sizeof(int));
	file.read((char*)&Start, sizeof(Date));
	file.read((char*)&End, sizeof(Date));
	Date now = GetTime();
	if (now < Start) { current = std::to_string(Start.dd) + "\\" + std::to_string(Start.mm) + "\\" + std::to_string(Start.yy); return 0; }// not in register time;
	else if (now >= Start && now <= End) {
		current = "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		return 1;// can register
	}
	else {//end register // save new score file and made current time semester to update file.
		current = "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
		Filelist* filelist = TakeFileInFolder(current);
		//std::cout << filelist->filename;
		int n = CountFile(filelist);
		for (int i = 0; i < n; i++) {
			Course* cour = BinToCourse(current + "\\" + filelist->filename);
			for (int m = 0; m < cour->numberofstudent; m++) {
				for (int n = m + 1; n < cour->numberofstudent; n++) {
					if (cour->stuID[m] > cour->stuID[n]) {
						unsigned __int64 k = cour->stuID[m];
						cour->stuID[m] = cour->stuID[n];
						cour->stuID[n] = k;
					}
				}
			}
			CourseToBin(cour, filelist->filename, current);
			SaveScore(cour, current + "\\" + filelist->filename + "Score");
			filelist = filelist->pNext;
		}
		file.close();
		_wremove(L"firstrun");

		file.open("currentsem", std::fstream::in | std::fstream::binary);
		if (file) {
			file.close();
			return 3;// currentsem has not end // sooooo....
		}

		file.open("currentsem", std::fstream::out | std::fstream::binary);
		file.write((char*)&year, sizeof(int));
		file.write((char*)&sem, sizeof(int));
		file.close();
		return 2;
	}
}