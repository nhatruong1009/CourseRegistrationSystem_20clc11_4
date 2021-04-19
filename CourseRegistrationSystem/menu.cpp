#include"menu.h"
#include"Data.h"
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
void userTypeMenu()
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
		studentMenu();
		return;
	case 1:
		staffMenu();
		return;
	case 2: return;
	}
}
void studentMenu()
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
		userTypeMenu();
		return;
	}
}
void staffMenu()
{
	int so;
	system("cls");
	std::cout << "-------------STAFF---------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Create a csvt"};
	menu[1] = new char[] {"Export scoreboard"};
	menu[2] = new char[] {"View semester time"};
	menu[3] = new char[] {"Back"};
	so = Menu(menu, 5, 2);
	DealocatedArrString(menu);
	switch (so)
	{
	case 0:
		return;
	case 1:
		return;
	case 2:
		ViewSemesterTime();
		return;
	case 3:
		userTypeMenu();
		return;
	}
}
