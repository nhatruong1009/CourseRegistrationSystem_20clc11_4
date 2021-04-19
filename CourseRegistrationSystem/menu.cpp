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
	int so;
	std::cout << "-------------USER TYPE---------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Student"};
	menu[1] = new char[] {"Academic Staff"};
	menu[2] = new char[] {"Back"};
	so = Menu(menu, 4, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0:
		studentMode();
		return;
	case 1:
		staffMode();
		return;
	case 2: return;
	}
}
void studentMode()
{
	int so;
	system("cls");
	std::cout << "-------------STUDENT---------------";
	char** menu = new char* [3];
	menu[0] = new char[] {"Log In"};
	menu[1] = new char[] {"Register"};
	menu[2] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0:
		std::cout << "   Ban da chon 1";
		return;
	case 1:
		std::cout << "   Ban da chon 2";
		return;
	case 2:
		userTypeMode();
		return;
	}
}
void staffMode()
{
	int so;
	system("cls");
	std::cout << "-------------STAFF---------------";
	char** menu = new char* [5];
	menu[0] = new char[] {"Student"}; // in side this, creative class / grande
	menu[1] = new char[] {"Course"}; // in side this, edit course 
	menu[2] = new char[] {"School year"}; // make school plan
	menu[3] = new char[] {"View semester time"}; //change to another semester of any year(but can't changed if time out)
	menu[4] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0: staffStudentMenu(); return;
	case 1: return;
	case 2: return;
	case 3: return;
	case 4: userTypeMode(); return;
	}
}

void staffStudentMenu() {
	int so;
	system("cls");
	std::cout << "------- Student Infomation ---------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Grade"};
	menu[1] = new char[] {"Class"};  
	menu[2] = new char[] {"Student"}; 
	menu[3] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0: gradeMenu(); return;
	case 1: classMenu(); return;
	case 2: studentMenu(); return;
	case 3: staffMode(); return;
	}
}

void gradeMenu() {
	int so;
	system("cls");
	std::cout << "------------ Grade --------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Add Grade"}; 
	menu[1] = new char[] {"View Grade"};  
	menu[2] = new char[] {"Remove Grade"};
	menu[3] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0: addGrade(); return;
	case 1: ViewGrade(); return;
	case 2: return;
	case 3: staffStudentMenu(); return;
	}
}
void classMenu() {
	int so;
	system("cls");
	std::cout << "------------ Class --------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Add Class"}; 
	menu[1] = new char[] {"View Class"};  
	menu[2] = new char[] {"Remove Class"}; 
	menu[3] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0: return;
	case 1: return;
	case 2: return;
	case 3: staffStudentMenu(); return;
	}
}
void studentMenu() {
	int so;
	system("cls");
	std::cout << "------------ Student --------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Add Student"};
	menu[1] = new char[] {"View Student"}; 
	menu[2] = new char[] {"Remove Student"}; 
	menu[3] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0: return;
	case 1: return;
	case 2: return;
	case 3: staffStudentMenu(); return;
	}
}

void addGrade() {
	system("cls");
	std::cout << "Grande: ";
	int grade;
	std::cin >> grade;
	SchoolYear* a = AddSchoolYear(grade);
	SaveSchoolYear(a);
}

void ViewGrade() {
	Filelist* list = TakeFileInFolder("Data\\Grade");
}