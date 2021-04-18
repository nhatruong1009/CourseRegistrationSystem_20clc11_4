#include"CommonFunc.h"
#include"Data.h"
using namespace std;

bool isLoggedIn() {
	std::wstring username, password, un, pw;
	std::wcout << "Enter username: ";
	std::wcin >> username;
	std::wcout << "Enter password: ";
	std::wcin >> password;
	std::wifstream read("testLogIn\\testLogIn.txt");
	std::getline(read, un);
	std::getline(read, pw);
	if (un == username && pw == password) return true;
	return false;
}
void userTypeMenu();
void studentMenu();
void staffMenu();

//
void enrollCourse(Student student, Course course) {
	//so luong course da dang ky, max 5
	int countCourse = student.coursenow ? _msize(student.coursenow) / sizeof(char*) : 0;

	if (countCourse >= 5 && course.numberofstudent >= course.maxstudent) {
		// cant enroll
		return;
	}
	for (int i = 0; i < countCourse; i++) {
		for (int j = 0; j < 2; ++j) {
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

void updateStudentsInClass(Classes a) {
	_SText();
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

	int so;
	cout << "-------------USER TYPE---------------" << endl;
	cout << "  1. Student" << endl;
	cout << "  2. Academic Staff" << endl;
	cout << "  3. Back " << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;

		switch (so)
		{
		case 1:
			studentMenu();
			return;
		case 2:
			staffMenu();
			return;
		case 3: return;
		}

	} while (1);
}
void studentMenu()
{
	int so;
	cout << "-------------STUDENT---------------" << endl;
	cout << "  1. Log In" << endl;
	cout << "  2. Register" << endl;
	cout << "  3. Back" << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;
		switch (so)
		{
		case 1:
			cout << "   Ban da chon 1" << endl;
			return;
		case 2:
			cout << "   Ban da chon 2" << endl;
			return;
		case 3:
			userTypeMenu();
			return;
		}
	} while (1);
}
void staffMenu()
{
	int so;
	cout << "-------------STAFF---------------" << endl;
	cout << "  1. Create a csvt" << endl;
	cout << "  2. Export scoreboard" << endl;
	cout << "  3. Back" << endl;
	do
	{
		cout << "Your choice: ";
		cin >> so;
		switch (so)
		{
		case 1:
			return;
		case 2:

			return;
		case 3:
			userTypeMenu();
			return;
		}
	} while (1);
}
