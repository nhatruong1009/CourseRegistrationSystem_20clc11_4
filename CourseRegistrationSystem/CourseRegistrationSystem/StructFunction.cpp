#include"NewStructs.h"
#include"DataControl.h"
#include<fstream>
#include <codecvt>
#include <locale>

std::ostream& operator<<(std::ostream& os, const Date& dt)
{
	os << dt.dd << '/' << dt.mm << '/' << dt.yy;
	return os;
}
std::wostream& operator<<(std::wostream& os, const Date& dt)
{
	os << dt.dd << '/' << dt.mm << '/' << dt.yy;
	return os;
}
std::wfstream ReadFileInCodecvt_utf8(std::wstring filename, int mode) {
	std::wfstream fi(filename, mode);
	fi.imbue(std::locale(fi.getloc(), new std::codecvt_utf8_utf16<wchar_t>));
	return fi;
}
bool CheckEnoughColumn(std::wstring str,int n) {
	int k = 1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == L',') { 
			k += 1;
			if (k == n) {return true; }
		}
	}
	return false;
}
void cinclear() {
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Student InputStudent() {
	Student stu;
	std::wstring temp;
	std::cout << "ID: "; std::cin >> stu.ID;
	cinclear();
	std::cout << "Fist name: "; std::getline(std::wcin,temp);
	stu.fistname = new wchar_t[temp.length()+1];
	stu.fistname[temp.length()] = '\0';
	temp.copy(stu.fistname, temp.length());
	std::cout << "Last name: "; std::getline(std::wcin, temp);
	stu.lastname = new wchar_t[temp.length() + 1];
	stu.lastname[temp.length()] = '\0';
	temp.copy(stu.lastname, temp.length());
	std::cout << "Gender: "; std::cin >> stu.gender;
	stu.fistname[temp.length()] = '\0';
	cinclear();
	std::cout << "Birth: "; std::wcin >> temp;
	wchar_t* temp1 = new wchar_t[temp.length() + 1];
	temp1[temp.length()] = '\0';
	temp.copy(temp1, temp.length());
	stu.birth = StringToDate(temp1);
	cinclear();
	std::cout << "Social ID: "; std::cin >> stu.SocialID;
	std::wstring user = std::to_wstring(stu.ID);
	stu.account.username = new wchar_t[user.length() + 1];
	stu.account.username[user.length()] = '\0';
	user.copy(stu.account.username, user.length());
	stu.account.password = new char[7];
	strcpy_s(stu.account.password, 7, "123456\0");
	cinclear();
	return stu;
}
void AddStudent(_Student *&studentlist, Student student) {
	if (studentlist == nullptr) { studentlist = new _Student{ student }; studentlist->pNext = studentlist, studentlist->pPrev = studentlist; return; }
	studentlist->pPrev = new _Student{ student,studentlist,studentlist->pPrev };
	studentlist->pPrev->pPrev->pNext = studentlist->pPrev;
}
_Student* AddStudent(std::wstring filein) {
	std::wfstream fi = ReadFileInCodecvt_utf8(filein, std::wfstream::in);
	if (!fi) { std::cout << "can't open"; return nullptr; }
	std::wstring temp;
	std::getline(fi, temp);
	if (!CheckEnoughColumn(temp, 7)) { fi.close(); return nullptr; }//not enough columns
	_Student* stu = nullptr;
	AddStudent(stu, StringToStudent(temp));
	while (fi)
	{
		std::getline(fi, temp);
		if(temp.length()!=0)AddStudent(stu, StringToStudent(temp));
	}
	fi.close();
	return stu;
}
void FileOutStudent(_Student* stu,std::wstring fileout) {
	if (stu == nullptr) { return; }
	std::wfstream fi(fileout, std::wfstream::out);
	fi << L"ï»¿";
	fi.close();
	fi = ReadFileInCodecvt_utf8(fileout, std::wfstream::app);
	_Student* temp = stu;
	do
	{
		fi << stu->student.ID << ',' << stu->student.fistname << ',' << stu->student.lastname << ',' << stu->student.gender << ',' << stu->student.birth << ',' << stu->student.SocialID << '\n';
		stu = stu->pNext;
	} while (stu != temp);
	fi.close();
}
int NumberOfStudent(_Student* stu) {
	if (stu == nullptr) return 0;
	int k = 0;
	_Student* temp = stu;
	do {
		k += 1;
		stu = stu->pNext;
	} while (stu != temp);
	return k;
}
void PrintStu(Student *a) {
	std::wcout << a->ID << '\n';
	std::wcout << a->fistname << '\n';
	std::wcout << a->lastname << '\n';
	std::wcout << a->gender << '\n';
	std::wcout << a->birth << '\n';
	std::wcout << a->SocialID << '\n';
	std::wcout << a->account.username << '\n';
	std::wcout << a->account.password << '\n';
}
void PrintStu(_Student* stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	do
	{
		PrintStu(&stu->student);
		stu = stu->pNext;
	} while (stu != temp);
}
Student* FindStudent(_Student* studentlist, unsigned __int32 ID) {
	_Student* temp = studentlist;
	while (studentlist->student.ID != ID && studentlist->pNext != temp)
	{
		studentlist = studentlist->pNext;
	}
	if (studentlist->student.ID != ID) { return nullptr; }
	return &studentlist->student;
}
void DealloStu(_Student*& stu) {
	if (stu == nullptr) return;
	_Student* temp = stu;
	do {
		_Student* a = stu;
		stu = stu->pNext;
		delete a;
	} while (stu != temp);
}
void RemoveStudent(_Student*& studentlist, unsigned __int32 ID) {
	_Student* temp = studentlist;
	_Student* pcur = studentlist;
	while (pcur->student.ID != ID && pcur->pNext != temp)
	{
		pcur = pcur->pNext;
	}
	if (studentlist->student.ID != ID) return;
	pcur->pPrev->pNext = pcur->pNext;
	pcur->pNext->pPrev = pcur->pPrev;
	delete pcur;
}

Classes InputClass(std::wstring name,_Student* stu=nullptr){
	Classes newclass;
	newclass.name = new wchar_t[name.length() + 1];
	newclass.name[name.length()] = '\0';
	name.copy(newclass.name, name.length());
	if (stu == nullptr) { return newclass; }
	newclass.student = new Student [NumberOfStudent(stu)];
	_Student* temp = stu;
	int k = 0;
	do {
		newclass.student[k] = stu->student;
		k += 1;
		stu = stu->pNext;
	} while (stu != temp);
	return newclass;
}

Score InputScore();
void AddScore(Score* scoreboard, Score score);
Score* InputScore(std::string filein);

void AddClass(SchoolYear schoolyear, Classes classes);
void AddClass(SchoolYear schoolyear, std::string filein);
Student* FindStudent(_Student student, char* username);
Course* FindCourse(_Course course, char* ID);
Course* FindCourse(SchoolYear schoolyear, char* ID);
Course* FindCourse(SchoolYear* schoolyear, char* ID);
Score FindScore(char* courseID, unsigned int studentID);
Classes* FindClass(SchoolYear* schoolyear, char* classname);
void AddCourse(_Course courselist, Course course);
_Course* InputCorse(std::string filein);
