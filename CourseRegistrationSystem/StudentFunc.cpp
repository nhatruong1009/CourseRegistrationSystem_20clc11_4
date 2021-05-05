#include"Student.h"

void SaveLoginHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\login.txt", std::ios::app);
	file << AccountUsername << " " << a;
	file.close();
}
void SaveLogoutHistory(char* AccountUsername)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\logout.txt", std::ios::app);
	if (!file) return;
	file << AccountUsername << " " << a;
	file.close();
}
void SaveCourseRegHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursereg.txt", std::ios::app);
	if (!file) return;
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}
void SaveCourseCancelHis(char* AccountUsername, Course course)
{
	__time32_t now = time(0);
	char a[100];
	_ctime32_s(a, &now);
	std::ofstream file;
	file.open("History\\coursecancel.txt", std::ios::app);
	if (!file) return;
	file << AccountUsername << " " << course.ID << " " << a;
	file.close();
}

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
void studentMode(Student* stu){
	if (stu == nullptr){
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
		DealocatedArrString(menu);
		StuInformation(stu);
		break;
	case 1:
		DealocatedArrString(menu);
		CourseInformaion(stu);
		break;
	case -1:
	case 2:
		Logout(stu);
		deleteStu(stu);
		DealocatedArrString(menu);
		userTypeMode();
		break;
	}
}
void StuInformation(Student* stu) {
	system("cls");
	std::cout << "Student ID: " << stu->ID << '\n';
	_LText();
	std::wcout << "Name: " << stu->firstname << "\t" << stu->lastname << "\n";
	_SText();
	std::cout << "Birth: " << stu->birth << "\t\t" << "Social ID: " << stu->SocialID << '\n';
	std::cout << "Gender: "; stu->gender == 'M' ? std::cout << "Men\n" : std::cout << "Women\n";
	std::cout << "GPA: " << stu->GPA << '\n';

	char** menu = new char* [2];
	menu[0] = new char[] {"Change Infomation"};
	menu[1] = new char[] {"Return"};
	switch (Menu(menu, 5, 7))
	{
	case 0: 
		DealocatedArrString(menu);
		ChangeInfo(stu);
	case-1:
	case 1:
		DealocatedArrString(menu);
		studentMode(stu);
		break;
	}
}
void ViewCourseNow(Student* stu) {
	system("cls");
	std::cout << "------------- Registed Course ---------------";
	if (stu->coursenow == nullptr) { std::cout << "\n_Empty_\n> Return <";	CourseInformaion(stu); _getwch(); return; }
	int n = _msize(stu->coursenow) / sizeof(char*);
	char sem = stu->coursenow[0][strlen(stu->coursenow[0]) - 1];
	char y[5];
	ToString(stu->coursenow[0]).copy(y, 4, strlen(stu->coursenow[0]) - 5);
	y[4] = '\0';
	std::cout << "[]" << sem << ":" << y;
	_getwch();
	CourseInformaion(stu);
}
void CourseInformaion(Student* stu) {
	system("cls");
	std::cout << "------------- Course ---------------";
	char** menu = new char* [4];
	menu[0] = new char[] {"Register Course"};
	menu[1] = new char[] {"Regsited Couse"};
	menu[2] = new char[] {"Completed Courses"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2)) {
	case 0: DealocatedArrString(menu);  registerMenu(stu); break;
	case 1: DealocatedArrString(menu); ViewCourseNow(stu); break;
	case 2: DealocatedArrString(menu); ViewCouse(stu); break;
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
	if (stu->allcourse == nullptr) { std::cout << "\n_Empty_\n> Return <";	CourseInformaion(stu); _getwch(); return; }
	int n = _msize(stu->allcourse) / sizeof(char*);
	_getwch();
	CourseInformaion(stu);
}
void registerMenu(Student* stu) {
	std::string current;
	fistrun(current);
	Filelist* filelist = TakeFileInFolder(current);
	if (filelist == nullptr) return;
	int n = CountFile(filelist);
	Course** course = new Course * [n];
	int m = 0;
	if (stu->coursenow != nullptr) m = _msize(stu->coursenow) / sizeof(stu->coursenow);
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
	deleteCourse(course);
	deleteFilelist(filelist);
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
void takeCourseReg(Course** course, int*& take, Student* stu, std::string current) {
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
		else if (get == 'S' || get == KEY_DOWN) {
			if (index < n - 1) {
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
	} while (get != 'E');
	// phan loai mon sau do save
	std::cout << "out";
	Course** newReg = nullptr;
	Course** cancelReg = nullptr;

	classifyCourse(reg, wasreg, cancelReg, newReg);
	registerCourse(newReg, current, stu->ID);
	cancelCourse(cancelReg, current, stu->ID);
	registerCourse(stu, reg, current);
	delete[] reg, newReg, cancelReg, newReg;
}
void LoginStu(Student*& CurrentUser)
{
	system("cls");	//clear the screen
	std::string U, P;
	if (std::cin.tellg() != 0) std::cin.clear();
	do
	{
		std::cout << "----------- Login -----------\n";
		std::cout << "Username: ";
		std::getline(std::cin, U);
		std::cout << "Password: ";
		P = InputHidden();
		if (P == "") { CurrentUser = 0; break; }// don't input password;
		std::string foldername = "K20";
		foldername = foldername + U[0] + U[1];
		if (U.size() < 8)
		{
			system("cls");
			std::cout << "Username must be a 8-digit number, please try again." << std::endl;
			continue;
		}
		Student* a = BinToStu("Data\\Grade\\" + foldername + "\\Student\\" + U);
		if (a == nullptr)
		{
			system("cls");
			std::cout << "Username is invalid, please try again." << std::endl;
			continue;
		}
		if (P.compare(ToString(a->account.password)) == 0)
		{
			CurrentUser = a;
			SaveLoginHistory(a->account.username);
			break;
		}
		else { system("cls"); std::cout << "Password is invalid, please try again. " << std::endl; }
		deleteStu(a);
	} while (1);
	// Go to Student menu
}
void Logout(Student* CurrentUser)
{
	system("cls");
	SaveLogoutHistory(CurrentUser->account.username);
}
void ChangePassword(Student* CurrentUser)
{

	system("cls");
	std::string pass1, pass2;
	do
	{
		std::cout << "New password: \t\t";
		pass1 = InputHidden();
		std::cout << "Confirm password: \t";
		pass2 = InputHidden();
		if (pass1 != pass2) std::cout << "Your password and confirmation password do not match, try again." << std::endl << std::endl;
	} while (pass1 != pass2);
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	delete[] CurrentUser->account.password;
	CurrentUser->account.password = StrToChar(pass1);
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	short n;
	std::cout << "Change successfully " << std::endl;
	std::cout << "\n> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}
void ChangeSocialID(Student* CurrentUser)
{
	system("cls");
	unsigned __int64 newSocialID1, newSocialID2;
	do
	{
		std::cout << "New Social ID:\t\t";
		newSocialID1 = InputNumber();
		std::cout << "Confirm new Social ID:\t";
		newSocialID2 = InputNumber();
		if (newSocialID1 != newSocialID2)
			std::cout << "New Social ID and Confirm Social ID do not match, try again " << std::endl << std::endl;
	} while (newSocialID1 != newSocialID2);
	std::cout << "Change succesfully " << std::endl;
	CurrentUser->SocialID = newSocialID1;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	std::cout << "> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}
void ChangeDOB(Student* CurrentUser)
{
	system("cls");
	Date dat;
	while (1)
	{
		std::cout << "Birth: ";
		dat = InputDate();
		if (dat.dd == 0) { dat = { 1,1,2000 }; }
		if (CheckDate(dat))
			break;
		else
		{
			std::cout << "Date is invalid, try again. " << std::endl << std::endl;
			continue;
		}
	}
	std::cout << "Change successfully " << std::endl;
	CurrentUser->birth = dat;
	std::string foldername = "K20"; // 21st century, will update later when 22nd century come
	foldername = foldername + CurrentUser->account.username[0] + CurrentUser->account.username[1];
	StuToBin(CurrentUser, "Data\\Grade\\" + foldername + "\\Student\\" + ToString(CurrentUser->account.username));
	std::cout << "\n> Go back <";
	_getwch();
	ChangeInfo(CurrentUser);
}
void ChangeInfo(Student*& CurrentUser)
{
	system("cls");
	char** menu = new char* [4];
	menu[0] = new char[] {"Password"};
	menu[1] = new char[] {"Date Of Birth"};
	menu[2] = new char[] {"Social ID"};
	menu[3] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0:
		DealocatedArrString(menu);
		ChangePassword(CurrentUser);
		break;
	case 1:
		DealocatedArrString(menu);
		ChangeDOB(CurrentUser);
		break;
	case 2:
		DealocatedArrString(menu);
		ChangeSocialID(CurrentUser);
		break;
	case 3:
	case -1:
		DealocatedArrString(menu);
		break;
		StuInformation(CurrentUser);
	}
}
