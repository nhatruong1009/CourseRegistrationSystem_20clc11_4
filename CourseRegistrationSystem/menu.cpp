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
	menu[2] = new char[] {"Exit"};
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
void studentMode(Student* stu )
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
		DealocatedArrString(menu);
		return;
	case 1:
		CourseInformaion(stu);
		DealocatedArrString(menu);
		return;
	case -1:
	case 2:
		userTypeMode();
		DealocatedArrString(menu);
		return;
	}
}
void staffMode()
{
	system("cls");
	std::cout << "-------------STAFF---------------";
	char** menu = new char* [5];
	menu[0] = new char[] {"Student"}; // in side this, creative class / grande
	menu[1] = new char[] {"Course"}; // in side this, edit course 
	menu[2] = new char[] {"School year"}; // make school plan
	menu[3] = new char[] {"View semester time"}; //change to another semester of any year(but can't changed if time out)
	menu[4] = new char[] {"Back"};
	switch (Menu(menu, 5, 2))
	{
	case 0: staffStudentMenu(); DealocatedArrString(menu); return;
	case 1: DealocatedArrString(menu); return;
	case 2: DealocatedArrString(menu); return;
	case 3: DealocatedArrString(menu); return;
	case -1:
	case 4: userTypeMode(); DealocatedArrString(menu); return;
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
	case 0: gradeMenu(); DealocatedArrString(menu); return;
	case 1: classMenu(); DealocatedArrString(menu); return;
	case 2: studentMenu(); DealocatedArrString(menu); return;
	case-1:
	case 3: staffMode(); DealocatedArrString(menu); return;
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
	case 0: addGrade(); DealocatedArrString(menu); return;
	case 1: ViewGrade(); DealocatedArrString(menu); return;
	case-1:
	case 2: staffStudentMenu(); DealocatedArrString(menu); return;
	}
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
	case 0: AddClass(); DealocatedArrString(menu); return;
	case 1: ViewClass();  DealocatedArrString(menu); return;
	case-1:
	case 2: staffStudentMenu();	DealocatedArrString(menu); return;
	}
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
	case 0: DealocatedArrString(menu); return;
	case 1: DealocatedArrString(menu); return;
	case-1:
	case 2: staffStudentMenu();	DealocatedArrString(menu); return;
	}
}
void addGrade() {
	system("cls");
	std::cout << "---------- Add Grande ----------";
	std::cout << "\nGrade: ";
	int grade;
	std::cin >> grade;
	SchoolYear* a = AddSchoolYear(grade);
	SaveSchoolYear(a);
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
			std::cout << ToString(list->filename);
			list = list->pNext;
		}
		
		GotoXY(5, 2 + index);
		std::cout <<"> "<<ToString(list->filename)<<" <";


		Filelist *listclass = TakeFileInFolder(L"Data\\Grade\\" + list->filename+L"\\Class");
		int n = CountFile(listclass);
		Classes** temp = new Classes*[n];
		for (int i = 0; i < n; i++) {
			std::wstring tempfile = L"Data\\Grade\\" + list->filename + L"\\Class\\" + listclass->filename;
			listclass = listclass->pNext;
			temp[i] = LoadClass(ToString(tempfile).c_str());
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
	std::wstring grade = ChoseFolder(list, 5, 2);
	if(grade !=L""){
		int year = StringToInt(&grade[1]);
		SchoolYear* newscholl = AddSchoolYear(year);
		SaveSchoolYear(newscholl);
	}

	//dealocated list here
	classMenu();
}

void DoSomeThingInClass(Classes* cls) {
	Student* stu = new Student[cls->numberofstudent];
}
void ViewClass() {
	system("cls");
	std::cout<<"---------- View Class ----------";
	Filelist* grade = TakeFileInFolder("Data\\Grade");
	std::wstring chosegrade = ChoseFolder(grade, 5, 2);
	if (chosegrade != L"") {
		Filelist* classlist = TakeFileInFolder("Data\\Grade\\" + ToString(chosegrade) + "\\Class");
		std::wstring choseclass = ChoseFolder(classlist, 20, 2);
		std::string classfile = "Data\\Grade\\" + ToString(chosegrade) + "\\Class" + ToString(choseclass);
		Classes* classnow = LoadClass(classfile.c_str());


		DoSomeThingInClass(classnow);
		//delete classnow here
		//do somthing with file class here
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
	switch (Menu(menu,5,7))
	{
	case 0: ChangeInfo(*stu);
	case-1:
	case 1:
		break;
	}

	DealocatedArrString(menu);
	studentMode(stu);
}

void CourseInformaion(Student* stu){

}
