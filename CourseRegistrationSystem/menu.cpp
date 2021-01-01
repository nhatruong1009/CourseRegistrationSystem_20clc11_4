#include"menu.h"
#include"Data.h"
#include"CommonFunc.h"
bool isLoggedIn() {
	_LText();
	std::wstring username, password, un, pw;
	std::wcout << "Enter username: ";
	std::wcin >> username;
	std::wcout << "Enter password: ";
	std::wcin >> password;
	std::wifstream read("testLogIn\\testLogIn.txt");
	std::getline(read, un);
	std::getline(read, pw);
	_SText();
	if (un == username && pw == password) return true;
	return false; 
}
void registerMenu(Student* stu);
void enrollCourse(Student student, Course course) {
	//so luong course da dang ky, max 5
	int countCourse = student.coursenow ? _msize(student.coursenow) / sizeof(char*) : 0;

	if (countCourse >= 5 && course.numberofstudent >= course.maxstudent) {
		// cant enroll
		return;
	}
	for (int i = 0; i < countCourse; i++) {
		for (int j = 0; j < 2; ++j) {
			//all course la lich su hoc ,minh phai so sanh voi course now thoi
			if (course.performed[0].session == student.allcourse[i][j] &&
				course.performed[1].session == student.allcourse[i][j] &&
				course.performed[0].day == student.allcourse[i][j] &&
				course.performed[1].day == student.allcourse[i][j]) {
				//cant enroll
				return;
			}
		}

	}
	//enroll
	student.coursenow[countCourse][0] = course.performed->day;
	student.coursenow[countCourse][1] = course.performed->session;
	//addStudent();

}
void updateStudentsInClass(Classes &a) {
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
void studentMode(Student* stu)
{
	if (stu == nullptr)
	{
		LoginStu(stu);
		if (stu == 0) { userTypeMode(); return; }
	}
	system("cls");
	std::cout << "-------------STUDENT---------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Infomation"};
	menu[1] = new char[] {"Course"};
	menu[2] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:
		StuInformation(stu);
		break;
	case 1:
		CourseInformaion(stu);
		break;
	case -1:
	case 2:
		Logout(stu);
		deleteStu(stu);
		DealocatedArrString(menu);;
		userTypeMode();
		break;
	}
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
	case 0: staffStudentMenu(); break;
	case 1: courseStaff(); break;
	case 2: schoolPlan(); break;
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
	case 0: gradeMenu(); break;
	case 1: classMenu(); break;
	case 2: studentMenu(); break;
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
	case 0: addGrade(); break;
	case 1: ViewGrade(); break;
	case-1:
	case 2: staffStudentMenu(); break;
	}
	DealocatedArrString(menu);
}
// now work here
void classMenu() {
	system("cls");
	std::cout << "------------ Class --------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Add Class"}; 
	menu[1] = new char[] {"View Class"};  
	menu[2] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: AddClass(); break;
	case 1: ViewClass();  break;
	case-1:
	case 2: staffStudentMenu();	break;
	}
	DealocatedArrString(menu);
}
void studentMenu() {
	system("cls");
	std::cout << "------------ Student --------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Add Student"};
	menu[1] = new char[] {"View Student"}; 
	menu[2] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: break;
	case 1: break;
	case-1:
	case 2: staffStudentMenu();	break;
	}
	DealocatedArrString(menu); 
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
	std::cout << " done";
	_getwch();
	//delete schoolyear here
	gradeMenu();
}
void ViewGrade() {
	Filelist* list = TakeFileInFolder("Data\\Grade");
	int size = CountFile(list);
	int index = 0;
	while(true){
		system("cls");
		std::cout << "-------------- View Grade ---------------";
		for (int i = 0; i < size; i++) {
			GotoXY(5, 2 + i);
			std::cout << list->filename;
			list = list->pNext;
		}
		
		GotoXY(5, 2 + index);
		std::cout <<"> "<<list->filename<<" <";


		Filelist *listclass = TakeFileInFolder("Data\\Grade\\" + list->filename+"\\Class");
		int n = CountFile(listclass);
		Classes** temp = new Classes*[n];
		for (int i = 0; i < n; i++) {
			std::string tempfile = "Data\\Grade\\" + list->filename + "\\Class\\" + listclass->filename;
			listclass = listclass->pNext;
			temp[i] = LoadClass(tempfile.c_str());
		}
		for (int i = 0; i < n; i++) {
			GotoXY(30, 2 + i);
			std::cout <<"Class: "<<temp[i]->name << "\t\t" << temp[i]->numberofstudent<<" students";
		}
		//should delete temp and listclass here
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
				//list delete here
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
	if(grade !=""){
		int year = StringToInt(&grade[1]);
		SchoolYear* newscholl = AddSchoolYear(year);
		SaveSchoolYear(newscholl);
	}

	//dealocated list here
	classMenu();
}

void DoSomeThingInClass(Classes* cls,std::string grade) {
	Student** teee = SearchStuArr(cls->ID, grade);

	char** menu = new char* [3];
	menu[0] = new char[] {"View"};
	menu[1] = new char[] {"Print out CSV"};
	menu[2] = new char[] {"back"};
	int chose = 0;
	while (chose!=-1 && chose!=2)
	{
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
}
void ViewClass() {
	system("cls");
	std::cout<<"---------- View Class ----------";
	Filelist* grade = TakeFileInFolder("Data\\Grade");
	std::string chosegrade = ChoseFolder(grade, 5, 2);
	if (chosegrade != "") {
		Filelist* classlist = TakeFileInFolder("Data\\Grade\\" + chosegrade + "\\Class");
		std::string choseclass = ChoseFolder(classlist, 20, 2);
		std::string classfile = "Data\\Grade\\" + chosegrade + "\\Class\\" + choseclass;
		Classes* classnow = LoadClass(classfile.c_str());


		DoSomeThingInClass(classnow, chosegrade);
		//delete classnow here
	}
	classMenu();
}



void StuInformation(Student* stu){
	system("cls");
	std::cout << "Student ID: " << stu->ID<<'\n';
	_LText();
	std::wcout <<"Name: " <<stu->firstname << "\t" << stu->lastname << "\n";
	_SText();
	std::cout << "Birth: " << stu->birth << "\t\t" << "Social ID: " << stu->SocialID<<'\n';
	std::cout << "Gender: "; stu->gender == 'M' ? std::cout << "Men\n" : std::cout << "Women\n";
	std::cout << "GPA: " << stu->GPA << '\n';

	char** menu = new char* [2];
	menu[0] = new char[] {"Change Infomation"};
	menu[1] = new char[] {"Return"};
	switch (Menu(menu, 5, 7))
	{
	case 0: ChangeInfo(stu);
	case-1:
	case 1:
		DealocatedArrString(menu);
		studentMode(stu);
		break;
	}
}

void viewCourseNow(Student* stu) {
	system("cls");
	std::cout << "------------- Registed Course ---------------";
	if (stu->coursenow == nullptr) { std::cout << "\n_Empty_\n> Return <"; _getwch(); return; }
	int n = _msize(stu->coursenow) / sizeof(char*);
	char sem = stu->coursenow[0][strlen(stu->coursenow[0]) - 1] + '0';
	char y[5];
	ToString(stu->coursenow[0]).copy(y, 4, strlen(stu->coursenow[0]) - 5);
	y[4] = '\0';
	std::cout << sem << y;
	_getwch();
}

void CourseInformaion(Student* stu){
	system("cls");
	std::cout << "------------- Course ---------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Register Course"};
	menu[1] = new char[] {"Regsited Couse"};
	menu[2] = new char[] {"Completed Courses"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2)) {
	case 0: registerMenu(stu); break;
	case 1: ViewCouse(stu); break;
	case 2: viewCourseNow(stu); break;
	case 3:
	case -1:
		DealocatedArrString(menu);
		studentMode(stu);
		break;
	}
}

void ViewCouse(Student* stu) {
	system("cls");
	std::cout << "------------- All Course ---------------";
	if (stu->allcourse == nullptr) { std::cout << "\n_Empty_\n> Return <"; _getwch(); return; }
	int n = _msize(stu->allcourse) / sizeof(char*);

	//Course*
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
	switch (Menu(menu,5,2))
	{
	case 0: addCourse(); break;
	case 1: viewCourse(); break;
	case 2: editCourse(); break;
	case 3:OpenRegister(); break;
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
	if (time == 0) {
		time = GetTime().yy; std::cout << time << '\n';
		MakeCurentTime(time);
		std::cout << "\n__________ Sucess _________";
		_getwch();
	}
	staffMode();
}

std::string chooseTime(bool timeout=true) {
	//system("cls");
	Filelist* list = TakeFileInFolder("Data\\SchoolYear");
	if (list != nullptr) {
		int n = CountFile(list);
		Date date;
		for (int i = 0; i < n; i++) {
			std::fstream fi("Data\\SchoolYear\\" + list->filename + "\\time", std::fstream::in | std::fstream::binary);
			for (int j = 0; j < 6; j++) {
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
		while (semester=="")
		{
			system("cls");
			std::string year = ChoseFolder(list, 5, 2);
			if (year == "") break;
			Filelist* sem = TakeFileInFolder("Data\\SchoolYear\\" + year);
			std::fstream fi("Data\\SchoolYear\\" + year + "\\time");
			for (int i = 0; i < 3; i++) {
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

void addCourseInSemmester(std::string current){
	system("cls");
	std::cout << current;
	std::cout << "\n--------- Add Course ---------";
	char** menu = new char*[3];
	menu[0] = new char[] { "From CSV" };
	menu[1] = new char[] {"Type in"};
	menu[2] = new char[] {"back"};
	switch (Menu(menu,5,3))
	{
	case 0: break;// csv in
	case 1: MakeCourse(current); break; // type in
	case-1:
	case 2:
		DealocatedArrString(menu);
		courseStaff();
		break;
	}
}

void addCourse(){
	system("cls");
	char** menu = new char* [3];
	menu[0] = new char[] {"Take by current time"};
	menu[1] = new char[] {"Choose time"};
	menu[2] = new char[] {"Back"};
	std::string current="";
	switch (Menu(menu,5,3))
	{
	case 0:current = TakeCurrent(); break;
	case 1: current = chooseTime(); break;
	case 2:
	case -1: break;
	}
	if (current != "") {
		addCourseInSemmester(current);
	}
	else{
		std::cout << "None Exits";
		_getwch();
	}
	DealocatedArrString(menu);
	courseStaff();
}

//tam thoi xong
void viewCourse(){
	std::string current = chooseTime(false);
	if (current != "") {
		Filelist* Cour = TakeFileInFolder(current);
		for (int i = 0; i < CountFile(Cour); i++) {
			if (Cour->filename.compare(Cour->filename.size() - 5, 5, "Score") == 0) { DeleteCurFileList(Cour); i -= 1; }
			else Cour = Cour->pNext;
		}
		Filelist* temp = Cour;
		system("cls");
		do {
			displayCourse(BinToCourse(current + "\\" + temp->filename));
			temp = temp->pNext;
		} while (temp != Cour);
		_getwch();
	}
	courseStaff();
}

void editCourse(){
	std::string current = chooseTime(false);
	if (current == "") return;
	system("cls");
	std::cout << "---------- Edit Course -----------";
	Filelist* Cour = TakeFileInFolder(current);
	if (CountFile(Cour)!=0) {
		for (int i = 0; i < CountFile(Cour); i++) {
			if (Cour->filename.compare(Cour->filename.size() - 5, 5, "Score") == 0) { DeleteCurFileList(Cour); i -= 1; }
			else Cour = Cour->pNext;
		}
		int n = CountFile(Cour);
		wchar_t** choseCourse = new wchar_t* [n];
		for (int i = 0; i < n; i++) {
			Course* temp = BinToCourse(current + "\\" + Cour->filename);
			choseCourse[i] = StrToChar(ToWstring(temp->ID) + L"  "+ ToWstring(temp->name));
			Cour = Cour->pNext;
			//delete temp here
		}
		int k = Menu(choseCourse, 5, 3);
		if (k !=-1) {
			Filelist* t = Cour;
			for (int i = 0; i < k; i++)t = t->pNext;
			editCourse(Cour->filename, current);
		}
	}
	else{
		std::cout << "\nNot available\n";
		std::cout << "> Back <";
	}
	courseStaff();
}
//maybe work
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

void timeRegister(std::string sem,Date startReg,Date endReg){
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
		switch (Menu(menu,5,3))
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
	if (sem == "") return;
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
		if (startReg>=endReg) std::cout << "Not Ivalid day\n";
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

void takeCourseReg(Course** course, int*& take,Student*stu,std::string current) {
	system("cls");
	int index = 0;
	int n = _msize(course) / sizeof(course);
	int had = 0;
	Course** reg = new Course * [5];
	Course** tempwasreg = new Course * [5];
	for (int i = 0; i < 5; i++) {
		reg[i] = nullptr;
	}
	for (int i = 0; i < n; i++) {
		GotoXY(4, i + 3);
		displaylistCourse(course[i]);
		if (take[i] == 1) { tempwasreg[had] = course[i]; reg[had] = course[i]; had += 1; }
	}
	Course** wasreg = nullptr;
	if (had != 0) {
		wasreg = new Course * [had];
		for (int i = 0; i < had; i++) {
			wasreg[i] = tempwasreg[i];
		}
	}
	delete[] tempwasreg;

	SessionConflict(course, reg, take);
	for (int i = 0; i < n; i++) {
		GotoXY(100, i + 3);
		if (take[i] == 1) { std::cout << 'O'; }
		else if (take[i] == -1) { std::cout << 'X'; }
		else std::cout << " ";
	}
	GotoXY(0, 3); std::cout << "->";
	char get;
	do
	{
		get = toupper(_getwch());
		if (get == 'W' || get == KEY_UP) {
			if (index > 0) {
				GotoXY(0, 3 + index);
				std::cout << "   ";
				index -= 1;
				GotoXY(0, 3 + index);
				std::cout << "->";
			}
		}
		else if(get=='S' || get==KEY_DOWN){
			if (index < n-1) {
				GotoXY(0, 3 + index);
				std::cout << "   ";
				index += 1;
				GotoXY(0, 3 + index);
				std::cout << "->";
			}
		}
		else if (get == KEY_ENTER) {
			if (take[index] == 1) {
				removereg(reg, course[index]);
				had -= 1;
				SessionConflict(course, reg, take);
				for (int i = 0; i < n; i++) {
					GotoXY(100, i + 3);
					if (take[i] == 1) { std::cout << 'O'; }
					else if (take[i] == -1) { std::cout << 'X'; }
					else std::cout << " ";
				}

			}
			else if (take[index] == 0 && had < 5) {
				reg[had] = course[index];
				had += 1;
				SessionConflict(course, reg, take);
				for (int i = 0; i < n; i++) {
					GotoXY(100, i + 3);
					if (take[i] == 1) { std::cout << 'O'; }
					else if (take[i] == -1) { std::cout << 'X'; }
					else std::cout << " ";
				}
			}
		}
	} while (get!='E');
	// phan loai mon sau do save
	std::cout << "out";
	Course** newReg = nullptr;
	Course** cancelReg = nullptr;

	classifyCourse(reg, wasreg, cancelReg, newReg);
	registerCourse(newReg, current, stu->ID);
	cancelCourse(cancelReg, current, stu->ID);
	registerCourse(stu, reg, current);

}

void registerMenu(Student*stu) {
	std::string current;
	fistrun(current);
	Filelist* filelist = TakeFileInFolder(current);
	if (filelist == nullptr) return;
	int n = CountFile(filelist);
	Course** course = new Course * [n];
	int m = 0;
	if(stu->coursenow!=nullptr) m = _msize(stu->coursenow) / sizeof(stu->coursenow);
 	int* canReg = new int[n];
	for (int i = 0; i < n; i++) {
		course[i] = BinToCourse(current + "\\" + filelist->filename);
		filelist = filelist->pNext;
		canReg[i] = 0;
		for (int j = 0; j < m; j++) {
			if (strncmp(stu->coursenow[j], course[i]->ID, strlen(course[i]->ID)) == 0) {
				canReg[i] = 1;
			}
		}
	}
	takeCourseReg(course, canReg, stu, current);

}