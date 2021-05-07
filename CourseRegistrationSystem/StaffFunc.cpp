#include"Staff.h"

SchoolYear* AddSchoolYear(int year) {
	wchar_t* data = new wchar_t[] {L"Data"};
	_wmkdir(data);
	delete[]data;
	data = new wchar_t[] {L"Data\\Grade"};
	_wmkdir(data);
	delete[] data;
	SchoolYear* a = new SchoolYear;
	a->year = year;
	wchar_t* yy = StrToChar(NumToLStr(a->year));
	wchar_t* file = new wchar_t[] { L"Data\\Grade\\K" };
	StrCat(file, wcslen(yy), yy);
	_wmkdir(file);
	wchar_t* temp = StrCat(file, L"\\Student");
	_wmkdir(temp);
	delete[] temp;
	temp = StrCat(file, L"\\Class");
	_wmkdir(temp);
	delete[] temp;
	a->classes = nullptr;
	a->student = nullptr;
	int chose;
	char** choselist = new char* [2];
	choselist[0] = new char[] {"AddClass"};
	choselist[1] = new char[] {"Done"};
	system("cls");
	chose = Menu(choselist, 5, 0);
	while (chose == 0)
	{
		Classes tt = MakeClass(a->student);
		AddClass(a->classes, tt);
		system("cls");
		std::cout << "------- Add Class -------";
		chose = Menu(choselist, 5, 1);
	}
	DealocatedArrString(choselist);
	delete[]yy, file;
	return a;
}
void SaveSchoolYear(SchoolYear* sch) {
	if (sch == nullptr) return;
	char* local = new char[] {"Data\\Grade\\K"};
	char* year = StrToChar(NumToStr(sch->year));
	char* direction = StrCat(local, year);
	SaveNewStu(sch->student, direction);
	SaveClass(sch->classes, direction);
	delete[]local, year, direction;
}
std::string TakeCurrent() {
	Filelist* Plan = TakeFileInFolder("Data\\SchoolYear");
	int n = CountFile(Plan);
	std::string year = "";
	char semester;
	Date temp = GetTime();
	Date start, end;
	std::fstream fi;
	for (int i = 0; i < n; i++) {
		fi.open("Data\\SchoolYear\\" + Plan->filename + "\\time", std::fstream::in | std::fstream::binary);
		for (int k = 0; k < 3; k++)
		{
			fi.read((char*)&start, sizeof(Date));
			fi.read((char*)&end, sizeof(Date));
			if (start >= temp) { year = Plan->filename; semester = k + 1 + '0'; }
		}
		Plan = Plan->pNext;
	}

	//deallocated plan here;
	if (year == "") return "";
	return "Data\\SchoolYear\\" + year + "\\Semester" + semester;
}
void MakeCurentTime(int year) {
	wchar_t* curent = new wchar_t[] {L"Data"};
	_wmkdir(curent);
	delete[] curent;
	curent = new wchar_t[] {L"Data\\SchoolYear"};
	_wmkdir(curent);
	wchar_t* temp = StrCat(curent, L"\\");
	delete[] curent;
	StrCat(temp, std::to_string(year).length(), std::to_wstring(year));
	if (_wmkdir(temp) == -1) { std::cout << "--Warning! override time--\n"; };
	StrCat(temp, 2, L"\\");
	for (int i = 0; i < 3; i++) {
		wchar_t* semester = StrCat(temp, L"Semester" + std::to_wstring(i + 1));
		_wmkdir(semester);
		delete[] semester;
	}
	wchar_t* SemesterTime = StrCat(temp, L"time");
	std::fstream fo(SemesterTime, std::fstream::out | std::fstream::binary);
	std::cin.clear();
	Date start[3], end[3];
	char** menu = new char* [2];
	menu[0] = new char[] {"Confirm"};
	menu[1] = new char[] {"Again"};
	do
	{
		for (int i = 0; i < 3; i++) {
			std::cout << "Date start semester " << i + 1 << ": ";
			while (true)
			{
				start[i] = InputDate();
				if (CheckDate(start[i]) == false || (i == 0 ? false : !(start[i] >= start[i - 1]))) {
					std::cout << "     Date not invalid! ";
				}
				else break;
			}
			std::cout << "Date end semester " << i + 1 << ": ";
			while (true)
			{
				end[i] = InputDate();
				if (CheckDate(end[i]) == false || end[i] < start[i] || (i == 0 ? false : !(end[i] >= end[i - 1]))) {
					std::cout << "     Date not invalid! ";
				}
				else break;
			}
		}
		system("cls");
		std::cout << "--------------------------------------------\n";
		for (int i = 0; i < 3; i++) {
			std::cout << "Semester " << i + 1 << "\t start: " << start[i] << "\tend:" << end[i] << '\n';
		}
	} while (Menu(menu, 6, 5) != 0);
	for (int i = 0; i < 3; i++) {
		fo.write((char*)&start[i], sizeof(Date));
		fo.write((char*)&end[i], sizeof(Date));
	}
	DealocatedArrString(menu);
	delete[] temp, SemesterTime;//
	fo.close();
}

void updateStudentsInClass(Classes& a) {
	std::cout << a.name << '\n';
	int n = _msize(a.ID) / sizeof(__int64);
	if (a.ID != nullptr) {
		for (int i = 0; i < n; i++) {
			std::cout << a.ID[i] << '\n';
		}
	}
}
void userTypeMode()
{
	system("cls");
	std::cout << "-------------USER TYPE---------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Student"};
	menu[1] = new char[] {"Academic Staff"};
	menu[2] = new char[] {"Exit"};
	switch (Menu(menu, 4, 2))
	{
	case 0:
		studentMode();
		break;
	case 1:
		staffMode();
		break;
	}
	DealocatedArrString(menu);
}
void staffMode()
{
	system("cls");
	std::cout << "-------------STAFF---------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Student"}; // in side this, creative class / grande
	menu[1] = new char[] {"Course"}; // in side this, edit course 
	menu[2] = new char[] {"School Plan"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:DealocatedArrString(menu); staffStudentMenu(); break;
	case 1:DealocatedArrString(menu); courseStaff(); break;
	case 2:DealocatedArrString(menu); schoolPlan(); break;
	case -1:
	case 3: DealocatedArrString(menu); userTypeMode(); break;
	}

}
void staffStudentMenu() {
	system("cls");
	std::cout << "------- Student Infomation ---------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Grade"};
	menu[1] = new char[] {"Class"};
	menu[2] = new char[] {"Student"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:DealocatedArrString(menu); gradeMenu(); break;
	case 1:DealocatedArrString(menu); classMenu(); break;
	case 2:DealocatedArrString(menu); studentMenuStaff(); break;
	case-1:
	case 3:DealocatedArrString(menu); staffMode(); break;
	}
}
void gradeMenu() {
	system("cls");
	std::cout << "------------ Grade --------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Add Grade"};
	menu[1] = new char[] {"View Grade"};
	menu[2] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:DealocatedArrString(menu); addGrade(); break;
	case 1:DealocatedArrString(menu); ViewGrade(); break;
	case-1:
	case 2:DealocatedArrString(menu); staffStudentMenu(); break;
	}
}
void classMenu() {
	system("cls");
	std::cout << "------------ Class --------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Add Class"};
	menu[1] = new char[] {"View Class"};
	menu[2] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: DealocatedArrString(menu); AddClass(); break;
	case 1: DealocatedArrString(menu); ViewClass();  break;
	case-1:
	case 2:DealocatedArrString(menu); staffStudentMenu();break;
	}
}

void StaffasStu() {
	system("cls");
	std::cout << "ID: ";
	unsigned __int64 id;
	std::cin >> id;
	Student* stu = BinToStu(GetFilePath(id));
	if(stu!=nullptr) studentMode(stu);
	else { std::cout << "Not have this ID student"; _getwch();	studentMenuStaff(); }
}
void studentMenuStaff() {
	system("cls");
	std::cout << "------------ Student --------------";
	char** menu = new char* [2];
	menu[0] = new char[] {"Login to a student"};
	menu[1] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: DealocatedArrString(menu); StaffasStu(); break;
	case-1:
	case 1:DealocatedArrString(menu); staffStudentMenu();	break;
	}
}
void addGrade() {
	system("cls");
	std::cout << "---------- Add Grande ----------";
	std::cout << "\nGrade: ";
	int grade;
	std::cin >> grade;
	SchoolYear* a = AddSchoolYear(grade);
	std::cout << "Saving..... ";
	SaveSchoolYear(a);
	deleteSchoolyear(a);
	std::cout << "\ndone";
	_getwch();
	//delete schoolyear here
	gradeMenu();
}
void ViewGrade() {
	Filelist* list = TakeFileInFolder("Data\\Grade");
	if (list == nullptr) {
		gradeMenu(); return;
	}
	int size = CountFile(list);
	int index = 0;
	while (true) {
		system("cls");
		std::cout << "-------------- View Grade ---------------";
		for (int i = 0; i < size; i++) {
			GotoXY(5, 2 + i);
			std::cout << list->filename;
			list = list->pNext;
		}

		GotoXY(5, 2 + index);
		std::cout << "> " << list->filename << " <";


		Filelist* listclass = TakeFileInFolder("Data\\Grade\\" + list->filename + "\\Class");
		int n = CountFile(listclass);
		Classes** temp = new Classes * [n];
		for (int i = 0; i < n; i++) {
			std::string tempfile = "Data\\Grade\\" + list->filename + "\\Class\\" + listclass->filename;
			listclass = listclass->pNext;
			temp[i] = LoadClass(tempfile.c_str());
		}
		for (int i = 0; i < n; i++) {
			GotoXY(30, 2 + i);
			std::cout << "Class: " << temp[i]->name << "\t\t" << temp[i]->numberofstudent << " students";
		}
		//should delete temp and listclass here
		deleteFilelist(listclass);
		deleteClasses(temp);
		char check = 0;
		while (true)
		{
			check = toupper(_getwch());
			if (check == 'W' || check == KEY_UP) {
				index == 0 ? index = size - 1 : index -= 1;
				list = list->pPrev;
				break;
			}
			else if (check == 'S' || check == KEY_DOWN) {
				index == size - 1 ? index = 0 : index += 1;
				list = list->pNext;
				break;
			}
			else if (check == KEY_ESC) {
				deleteFilelist(list);
				gradeMenu();
				return;
			}
		}
	}
}
void AddClass() {
	system("cls");
	std::cout << "----------- Add Class (chose grade) ------------\n";
	Filelist* list = TakeFileInFolder("Data\\Grade");
	std::string grade = ChoseFolder(list, 5, 2);
	if (grade != "") {
		int year = StringToInt(&grade[1]);
		SchoolYear* newscholl = AddSchoolYear(year);
		SaveSchoolYear(newscholl);
		deleteSchoolyear(newscholl);
	}

	deleteFilelist(list);
	classMenu();
}
void DoSomeThingInClass(Classes* cls, std::string grade) {
	Student** teee = SearchStuArr(cls->ID, grade);
	char** menu = new char* [3];
	menu[0] = new char[] {"View"};
	menu[1] = new char[] {"Print out CSV"};
	menu[2] = new char[] {"back"};
	int chose = 0;
	while (chose != -1 && chose != 2)
	{
		system("cls");
		chose = Menu(menu, 5, 2);
		switch (chose)
		{
		case 0:PrintStu(teee, 30); break;
		case 1:break;//cout somthing here
		case 2:
		case -1:
			break;
		}
	}
	deleteStu(teee);
	DealocatedArrString(menu);
}
void ViewClass() {
	system("cls");
	std::cout << "---------- View Class ----------";
	Filelist* grade = TakeFileInFolder("Data\\Grade");
	std::string chosegrade = ChoseFolder(grade, 5, 2);
	if (chosegrade != "") {
		Filelist* classlist = TakeFileInFolder("Data\\Grade\\" + chosegrade + "\\Class");
		std::string choseclass = ChoseFolder(classlist, 20, 2);
		std::string classfile = "Data\\Grade\\" + chosegrade + "\\Class\\" + choseclass;
		Classes* classnow = LoadClass(classfile.c_str());

		DoSomeThingInClass(classnow, chosegrade);
		//delete classnow here
		deleteClasses(classnow);
		deleteFilelist(classlist);
	}
	deleteFilelist(grade);
	classMenu();
}
void courseStaff() {
	system("cls");
	std::cout << "---------- Course ----------";
	char** menu = new char* [5];
	menu[0] = new char[] {"Add Course"};
	menu[1] = new char[] {"View Course"};
	menu[2] = new char[] {"Edit Course"};
	menu[3] = new char[] {"Open Register time"};
	menu[4] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: DealocatedArrString(menu); addCourse(); break;
	case 1: DealocatedArrString(menu); viewCourse(); break;
	case 2: DealocatedArrString(menu); editCourse(); break;
	case 3: DealocatedArrString(menu); OpenRegister(); break;
	case -1:
	case 4:
		DealocatedArrString(menu);
		staffMode();
		break;
	}

}
void schoolPlan() {
	int time;
	system("cls");
	std::cout << "--------- School Plan ---------";
	std::cout << "\nInput Year (Pass if take current year) :";
	time = InputNumber();
	if (time == -1) { staffMode(); return; }
	if (time == 0) {
		time = GetTime().yy; std::cout << time << '\n';
	}
	MakeCurentTime(time);
	std::cout << "\n__________ Sucess _________";
	_getwch();
	staffMode();
}
void addCourseInSemmester(std::string current) {
	system("cls");
	std::cout << current;
	std::cout << "\n--------- Add Course ---------";
	char** menu = new char* [3];
	menu[0] = new char[] { "From CSV" };
	menu[1] = new char[] {"Type in"};
	menu[2] = new char[] {"back"};
	switch (Menu(menu, 5, 3))
	{
	case 0: DealocatedArrString(menu); break;// csv in
	case 1: DealocatedArrString(menu); MakeCourse(current); break; // type in
	case-1:
	case 2:
		DealocatedArrString(menu);
		courseStaff();
		break;
	}
}
void addCourse() {
	system("cls");
	char** menu = new char* [3];
	menu[0] = new char[] {"Take by current time"};
	menu[1] = new char[] {"Choose time"};
	menu[2] = new char[] {"Back"};
	std::string current = "";
	switch (Menu(menu, 5, 3))
	{
	case 0: current = TakeCurrent(); break;
	case 1: current = chooseTime(); break;
	case 2:
	case -1:DealocatedArrString(menu);
		courseStaff();
		return;
	}
	if (current != "") {
		addCourseInSemmester(current);
	}
	else {
		std::cout << "None Exits";
		_getwch();
	}
	DealocatedArrString(menu);
	courseStaff();
}
void viewCourse() {
	std::string current = chooseTime(false);
	if (current != "") {
		Filelist* Cour = TakeFileInFolder(current);
		std::cout << CountFile(Cour);
		for (int i = 0; i < CountFile(Cour); i++) {
			if (Cour->filename.length() > 5 && Cour->filename.compare(Cour->filename.length() - 5, 5, "Score") == 0) { DeleteCurFileList(Cour); i -= 1; }
			else Cour = Cour->pNext;
		}
		Filelist* temp = Cour;
		system("cls");
		do {
			Course* k = BinToCourse(current + "\\" + temp->filename);
			displayCourse(k);
			deleteCourse(k);
			temp = temp->pNext;
		} while (temp != Cour);
		_getwch();
		deleteFilelist(Cour);
	}
	courseStaff();
}
void editCourse() {
	std::string current = chooseTime(false);
	if (current == "") { courseStaff(); return; }
	system("cls");
	std::cout << "---------- Edit Course -----------";
	Filelist* Cour = TakeFileInFolder(current);

	for (int i = 0; i < CountFile(Cour); i++) {
		if (Cour->filename.length() > 5 && Cour->filename.compare(Cour->filename.length() - 5, 5, "Score") == 0) { DeleteCurFileList(Cour); i -= 1; }
		else Cour = Cour->pNext;
	}


	if (CountFile(Cour) != 0) {
		int n = CountFile(Cour);
		wchar_t** choseCourse = new wchar_t* [n];
		for (int i = 0; i < n; i++) {
			Course* temp = BinToCourse(current + "\\" + Cour->filename);
			choseCourse[i] = StrToChar(ToWstring(temp->ID) + L"  " + ToWstring(temp->name));
			Cour = Cour->pNext;
			//delete temp here
			deleteCourse(temp);
		}
		int k = Menu(choseCourse, 5, 3);
		DealocatedArrString(choseCourse);
		if (k != -1) {
			Filelist* t = Cour;
			for (int i = 0; i < k; i++)t = t->pNext;
			editCourse(Cour->filename, current);
			deleteFilelist(t);
		}
	}
	else {
		std::cout << "\nNot available\n";
		std::cout << "> Back <";
	}
	courseStaff();
}
void resetRegister() {
	std::fstream file("firstrun", std::fstream::in | std::ios::binary);
	int year;
	int sem;
	file.read((char*)&year, sizeof(int));
	file.read((char*)&sem, sizeof(int));
	file.close();
	std::string current = "Data\\SchoolYear\\" + std::to_string(year) + "\\Semester" + std::to_string(sem);
	Filelist* filelist = TakeFileInFolder(current);
	if (filelist != nullptr) {
		Filelist* temp = filelist;
		do {
			Course* cou = BinToCourse(current + "\\" + temp->filename);
			cou->numberofstudent = 0;
			delete[]cou->stuID;
			CourseToBin(cou, temp->filename, current);
			filelist = filelist->pNext;
		} while (temp != filelist);
	}
}
void timeRegister(std::string sem, Date startReg, Date endReg) {
	int semester = sem[sem.length() - 1] - '0';
	char y[5];
	sem.copy(y, 4, sem.length() - 14);
	y[4] = '\0';
	int year = StringToInt(y);
	std::cout << semester << '\n';
	std::cout << year;
	std::fstream fo("firstrun", std::fstream::out | std::fstream::binary);
	fo.write((char*)&year, sizeof(int));
	fo.write((char*)&semester, sizeof(int));
	fo.write((char*)&startReg, sizeof(Date));
	fo.write((char*)&endReg, sizeof(Date));
	fo.close();
}
void OpenRegister() {
	system("cls");
	std::fstream file("firstrun", std::fstream::in | std::ios::binary);
	if (file) {
		file.close();
		std::cout << "Register time had made, you will override it and reset all register data after done!";
		char** menu = new char* [2];
		menu[0] = new char[] {"Confimn"};
		menu[1] = new char[] {"Cancel"};
		switch (Menu(menu, 5, 3))
		{
		case 0: DealocatedArrString(menu);  break;
		case 1:
		case -1:
			DealocatedArrString(menu);
			return;
		}
	}
	system("cls");
	std::cout << "------- Register time -------\n";
	std::cout << "     > pick Time <";
	if (_getwch() == KEY_ESC) return;
	std::string sem = chooseTime();
	if (sem == "") { std::cout << "Don't have any invalid semester!\n > Back <"; _getwch(); courseStaff(); return; }
	Date start = TakeDateStart(sem);
	Date End = TakeDateEnd(sem);
	Date startReg;
	Date endReg;
	system("cls");
	std::cout << "---------- Add Register time ----------\n";
	std::cout << "Semester start: " << start << "\tSemester end: " << End << '\n';
	do {
		std::cout << "End register date (before semester's start date): ";
		endReg = InputDate();
		if (endReg >= start) std::cout << "Not Ivalid day\n";
	} while (endReg >= start);
	do {
		std::cout << "Start register date(before register's end date): ";
		startReg = InputDate();
		if (startReg >= endReg) std::cout << "Not Ivalid day\n";
	} while (startReg >= endReg);
	system("cls");
	std::cout << "Confinm date\n";
	std::cout << "Start: " << startReg << "\tEnd:" << endReg << '\n';
	char** menu = new char* [2];
	menu[0] = new char[] {"Confimn"};
	menu[1] = new char[] {"Cancel"};
	switch (Menu(menu, 5, 4))
	{
	case 0:
		resetRegister();
		timeRegister(sem, startReg, endReg);
		break;
	case -1:
	case 1:
		break;
	}
	DealocatedArrString(menu);
	courseStaff();
}
std::string chooseTime(bool timeout) {
	//system("cls");
	Filelist* list = TakeFileInFolder("Data\\SchoolYear");
	if (list != nullptr) {

		int n = CountFile(list);
		Date date;
		for (int i = 0; i < n; i++) {
			std::fstream fi("Data\\SchoolYear\\" + list->filename + "\\time", std::fstream::in | std::fstream::binary);
			for (int j = 0; j < 5; j++) {
				fi.read((char*)&date, sizeof(Date));
			}
			if (date < GetTime() && timeout) {
				DeleteCurFileList(list);
				i -= 1; n -= 1;
			}
			else {
				list = list->pNext;
			}
			fi.close();
		}
		std::string semester = "";
		while (semester == "")
		{
			system("cls");
			std::string year = ChoseFolder(list, 5, 2);
			if (year == "") break;
			Filelist* sem = TakeFileInFolder("Data\\SchoolYear\\" + year);
			sem = sem->pPrev;
			DeleteCurFileList(sem);
			std::fstream fi("Data\\SchoolYear\\" + year + "\\time");
			fi.read((char*)&date, sizeof(Date));
			for (int i = 1; i < 3; i++) {
				fi.read((char*)&date, sizeof(Date));
				fi.read((char*)&date, sizeof(Date));
				if (date < GetTime() && timeout) { DeleteCurFileList(sem); }
				else { sem = sem->pNext; }
			}
			DeleteCurFileList(sem);
			semester = ChoseFolder(sem, 20, 2);
			if (semester != "") {
				return "Data\\SchoolYear\\" + year + "\\" + semester;
				std::fstream a;
			}
		}
	}
	return "";
}

unsigned short LStringToPerform(wchar_t* temp) {
	if (wcscmp(temp, L"Mon") == 0)return 0;
	if (wcscmp(temp, L"Tue") == 0)return 1;
	if (wcscmp(temp, L"Wed") == 0)return 2;
	if (wcscmp(temp, L"Thu") == 0)return 3;
	if (wcscmp(temp, L"Fri") == 0)return 4;
	if (wcscmp(temp, L"Sat") == 0)return 5;
	if (wcscmp(temp, L"Sun") == 0)return 6;
	if (wcscmp(temp, L"S1") == 0) return 0;
	if (wcscmp(temp, L"S2") == 0) return 1;
	if (wcscmp(temp, L"S3") == 0) return 2;
	if (wcscmp(temp, L"S4") == 0) return 3;
	return 0;
}
float StringToFloat(wchar_t* ch) {			// I added a commonFunc
	float a = 0;
	while (*ch != L'\0' && *ch != L'.')
	{
		a = a * 10 + *ch - L'0';
		ch++;
	}
	if (*ch == L'.') {
		ch++;
		while (*ch != L'/0') {
			a = a + (*ch - L'0') / 10;
			ch++;
		}
	}
	return a;
}
Course* StringToCourse(std::wstring str) {
	//ID, Course name, Teacher, Credit, Perform
	Course* cou = new Course;
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	_LText();

	cou->ID = new char[end - beg + 1];
	cou->ID[end - beg] = L'\0';
	LStrToStr(cou->ID, end - beg, temp);
	delete[] temp;

	beg = end + 1;
	end = str.find(L',', beg);
	cou->name = new wchar_t[end - beg + 1];
	cou->name[end - beg] = L'\0';
	str.copy(cou->name, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	cou->teacher = new wchar_t[end - beg + 1];
	cou->teacher[end - beg] = L'\0';
	str.copy(cou->teacher, end - beg, beg);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	cou->credit = unsigned short(StringToInt(temp));
	delete[]temp;

	for (int i = 0; i < 2; i++) {
		beg = end + 1;
		end = str.find(L',', beg);
		temp = new wchar_t[end - beg + 1];
		temp[end - beg] = L'\0';
		str.copy(temp, end - beg, beg);
		cou->performed[i].day = LStringToPerform(temp);
		delete[] temp;

		beg = end + 1;
		end = str.find(L',', beg);
		temp = new wchar_t[end - beg + 1];
		temp[end - beg] = L'\0';
		str.copy(temp, end - beg, beg);
		cou->performed[i].session = LStringToPerform(temp);
		delete[] temp;
	}

	return cou;
}
Course* searchID(_Course* courselist, std::wstring search) {
	int size = strlen(courselist->course->ID);
	wchar_t* t = new wchar_t[size];
	StrToLStr(t, size, courselist->course->ID);
	if (wcscmp(t, StrToChar(search)) == 0) {
		delete[]t;
		return courselist->course;
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
			return courselist->course;
		}
		delete[]t;
		courselist = courselist->pNext;
	}
	return nullptr;
}
Course* searchName(_Course* courselist, std::wstring search) {
	if (wcscmp(courselist->course->name, StrToChar(search)) == 0) return courselist->course;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course->name, StrToChar(search)) == 0) return courselist->course;
		courselist = courselist->pNext;
	}
	return nullptr;
}
Course* searchTeacher(_Course* courselist, std::wstring search) {
	if (wcscmp(courselist->course->teacher, StrToChar(search)) == 0) return courselist->course;
	_Course* first = courselist;
	courselist = courselist->pNext;
	while (courselist != first) {
		if (wcscmp(courselist->course->teacher, StrToChar(search)) == 0) return courselist->course;
		courselist = courselist->pNext;
	}
	return nullptr;
}
Course* searchCourse(_Course* courselist, std::wstring& search) {
	Course* result = nullptr;
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
_Course* FileInCourse(std::string filename) {
	_LText();
	std::wfstream fi(filename, std::wfstream::in);
	if (!fi) { return nullptr; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	fi.ignore(1i64, wchar_t(0xfeff));
	_Course* cou = nullptr;
	std::wstring temp;
	while (fi)
	{
		std::getline(fi, temp);
		if (temp.length() != 0) AddCourse(cou, StringToCourse(temp));
	}
	_SText();
	return cou;
}
void searchScore(_Course* allcourse) {
	_LText();
	bool flag = 0;
	int index;
	unsigned int id;
	std::wstring search;
	Course* cou = searchCourse(allcourse, search);
	system("cls");
	std::wcout << "Course: " << search << "\n";
	std::wcout << "Student ID: ";
	std::wcin >> id;
	std::wcin.ignore(1000, L'\n');

	if (cou->score != nullptr) {
		for (int i = 0; i < cou->numberofstudent; i++) {
			if (id == cou->score[i].ID) {
				index = i;
				flag = 1;
				break;
			}
		}
	}
	_SText();
	if (flag == 0) std::cout << "No score available\n";
	else displayScore(cou->score[index]);
}
void editCourse(Course* cou, std::string filename, std::string current) {
	char book;
	char** menu = new char* [3];
	menu[0] = new char[] {"Course info"};
	menu[1] = new char[] {"Students score"};
	menu[2] = new char[] {"Done"};
	while (1) {
		system("cls");
		std::cout << "----- Edit Course -----\n";
		book = Menu(menu, 5, 2);
		if (book == 2 || book == -1) break;
		if (book == 0) {
			editInfo(cou, filename, current);
		}
		else if (book == 1) {
			editScore(cou, filename, current);
		}
	}
	DealocatedArrString(menu);
}
void editInfo(Course* cou, std::string filename, std::string current) {
	if (GetTime() > TakeDateEnd(current)) {
		std::cout << "\nCourse had end, can't change"; 
		_getwch(); 
		editCourse(cou, filename, current);
		return;
	}
	char book;
	char** menu = new char*[5];
	menu[0] = new char[] {"Change teacher"};
	menu[1] = new char[] {"Change credits"};
	menu[2] = new char[] {"Change schedule"};
	menu[3] = new char[] {"Change max student"};
	menu[4] = new char[] {"Done"};
	while (1) {
		system("cls");
		displayCourse(cou);
		book = Menu(menu, 5, 20);
		if (book == 4 || book == -1) break;
		if (book == 0) {
			_LText();
			std::wcout << "New teacher: ";
			std::wcin.ignore(1000, '\n');
			std::wstring temp;
			std::getline(std::wcin, temp);
			delete[] cou->teacher;
			cou->teacher = StrToChar(temp);
			_SText();
		}
		else if (book == 1) {
			std::cout << "New credits: ";
			std::cin >> cou->credit;
			std::cin.ignore(1000, '\n');
		}
		else if (book == 2) {
			std::string check;
			fistrun(check);
			if (check == current) { std::cout << "\nCan't changed in register time"; break; }
			pickSchedule(cou, 0, 14);
		}
		else if (book == 3) {
			std::string check;
			fistrun(check);
			if (check == current) { std::cout << "\nCan't changed in register time"; break; }
			std::cout << "Max Student: ";
			std::cin >> cou->maxstudent;
			std::cin.ignore(1000, '\n');
		}
	}
	DealocatedArrString(menu);
	CourseToBin(cou, filename, current);
	editCourse(cou, filename, current);
}
void editScore(Course* cou, std::string filename, std::string current){
	if (secondrun().compare(current) != 0) { std::cout << "Cant change now"; _getwch(); return; }
	int test = current[current.length() - 1] - '0';
	Date start, end;
	char* file = new char[current.length() - 9];
	current.copy(file, current.length() - 9);
	file[current.length() - 10] = '\0';

	std::fstream fi(file, std::fstream::in | std::fstream::binary);
	for (int i = 0; i < test; i++) {
		fi.read((char*)&start, sizeof(Date));
		fi.read((char*)&end, sizeof(Date));
	}
	delete[] file;
	if (!(GetTime() > start && GetTime() < end)) { return; }

	std::cout << "ID: " << cou->ID << "\n";
	std::cout << "Course name: " << cou->name << "\n";
	_LText();
	std::wcout << "Teacher: " << cou->teacher << "\n";
	_SText();
	std::cout << "Number of students: " << cou->numberofstudent << "/" << cou->maxstudent << "\n\n";
	std::cout << "-----SCORE-----\n";
	for (int i = 0; i < cou->numberofstudent; i++) {  //print out students with numbers
		std::cout << "   " << i + 1 << ". ";
		displayScore(cou->score[i]);
		std::cout << "\n";
	}
	char book;
	int num;
	while (true) {
		do {
			GotoXY(0, 12 + 4 * cou->numberofstudent + 6);
			std::cout << "Pick a student (0. Stop):      ";
			GotoXY(26, 12 + 4 * cou->numberofstudent + 2);
			std::cin >> num;
		} while (num < 0 || num > cou->numberofstudent);
		if (num == 0) break;
		int X, Y;
		X = 3;
		Y = 6 + 4 * (num - 1) + 1;
		GotoXY(0, Y - 1);		//go to before student number
		std::cout << " >";
		while (true) {			//below is visually changing data
			book = _getwch();
			book = toupper(book);
			if (book == 'A' || book == KEY_LEFT) {
				GotoXY(X, Y);
				std::cout << "  ";
				if (X == 3) X = 45;
				if (X == 26) X == 3;
				if (X == 45) X = 26;
				GotoXY(X, Y);
				std::cout << ">>";
			}
			else if (book == 'D' || book == KEY_RIGHT) {
				GotoXY(X, Y);
				std::cout << "  ";
				if (X == 3) X = 26;
				if (X == 26) X == 45;
				if (X == 45)X = 3;
				GotoXY(X, Y);
				std::cout << ">>";
			}
			else if (book == KEY_ENTER || book == ' ') {
				if (X == 3) {
					GotoXY(16, Y);
					std::cout << "    ";
					GotoXY(16, Y);
					std::cin >> cou->score[num - 1].mids;
				}
				else if (X == 26) {
					GotoXY(36, Y);
					std::cout << "    ";
					GotoXY(36, Y);
					std::cin >> cou->score[num - 1].finals;
				}
				else if (X == 45) {
					GotoXY(56, Y);
					std::cout << "    ";
					GotoXY(56, Y);
					std::cin >> cou->score[num - 1].others;
				}
				GotoXY(16, Y + 1);
				std::cout << "    ";
				GotoXY(16, Y + 1);  // Not sure how to to calc totals score
				cou->score[num - 1].totals = cou->score[num - 1].mids + cou->score[num - 1].finals + cou->score[num - 1].others;
			}
			else if (book == KEY_ESC) {
				GotoXY(X, Y);
				std::cout << "  ";
				GotoXY(0, Y - 1);
				std::cout << "  ";
				break;
			}
		}
	}
}
void FileInScore(Course* cou, std::string direction) {		// I don't know file direction
	_LText();
	std::wfstream fi(direction, std::wfstream::in);
	if (!fi) { return; }
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8<wchar_t>));
	fi.ignore(1i64, wchar_t(0xfeff));
	std::wstring str;
	std::getline(fi, str);


	int stu_num;
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	stu_num = StringToInt(temp);
	delete[] temp;


	for (int i = 0; i < stu_num; i++) {
		std::getline(fi, str);
		if (str.length() != 0) StringToScore(cou->score[i], str);
	}
	_SText();
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
void StringToScore(Score& a, std::wstring str) {
	//ID, Course name, Teacher, Credit, Perform
	wchar_t* temp = nullptr;
	int beg = str.find(L',', 0) + 1;
	int end = str.find(L',', beg);

	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);

	a.ID = unsigned int(StringToInt(temp));
	delete[]temp;

	_LText();

	beg = end + 1;
	end = str.find(L',', beg);
	a.name = new wchar_t[end - beg + 1];
	a.name[end - beg] = L'\0';
	str.copy(a.name, end - beg, beg);

	_SText();

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	a.mids = StringToFloat(temp);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	a.finals = StringToFloat(temp);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	a.others = StringToFloat(temp);

	beg = end + 1;
	end = str.find(L',', beg);
	temp = new wchar_t[end - beg + 1];
	temp[end - beg] = L'\0';
	str.copy(temp, end - beg, beg);
	a.totals = StringToFloat(temp);
}
void editCourse(std::string filename, std::string current) {
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
	case 0: editCourse(cour, filename, current); break;
	case 1: 
		std::string check;
		fistrun(check);
		if (check == current || TakeDateStart(current) < GetTime()) {
			std::cout << "Can't be deleted";
		}
		else {
			deleteCourse(cour, filename, current);
			std::cout << "Success";
		}
		_getwch();
		break;
	}
	deleteCourse(cour);
}
void deleteCourse(Course* cour, std::string filename, std::string current) {

}
void displayScore(Score a) {
	_LText();
	std::wcout << "Name: " << a.name;
	std::wcout << "    ID: " << a.ID;
	std::wcout << "\n" << std::setw(16) << "Mid term: " << std::setw(4) << a.mids;
	std::wcout << std::setw(16) << "Final: " << std::setw(4) << a.finals;
	std::wcout << std::setw(16) << "Others: " << std::setw(4) << a.others;
	std::wcout << "\n" << std::setw(16) << "Total: " << a.totals << "\n";
	_SText();
}
