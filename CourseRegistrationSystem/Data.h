 #ifndef _Structs
#define _Structs
#include<iostream>
#include <iomanip>
#include<locale>
#include<codecvt>
#include<string>
struct Date
{
	unsigned int dd = 0, mm = 0, yy = 0;
};
struct Account
{
	char* username;
	char* password;
};
struct Score
{
	Score* pPrev;
	unsigned int ID;
	wchar_t* name;
	float totals, finals, mids, others;
	Score* pNext;
};
struct Course
{
	char* ID;
	wchar_t* name;
	wchar_t* teacher;
	unsigned short credit;
	struct Performed
	{
		unsigned short day=0;
		unsigned short session=0;
	};
	Performed performed[2];
	unsigned short numberofstudent = 0;
	unsigned short maxstudent = 50;
	unsigned __int64* stuID;
	Score* score=nullptr;
};
struct Student
{
	unsigned __int64 ID;
	wchar_t* firstname, * lastname;
	char gender;
	Date birth;
	unsigned __int64 SocialID;
	char** coursenow = nullptr;
	char** allcourse = nullptr;
	Account account;
	float GPA = 0;
};
struct Classes
{
	char* name;
	int numberofstudent=0;
	unsigned __int64* ID = nullptr;
};
struct _Student
{
	Student* student;
	_Student* pNext;
	_Student* pPrev;
};
struct _Class
{
	Classes classes;
	_Class* pNext;
	_Class* pPrev;
};
struct _Course
{
	Course* course;
	_Course* pNext;
	_Course* pPrev;
};
struct Semester
{
	Date start, end;
	_Course* course;
};
struct SchoolYear
{
	int year;
	Semester* semester;
	_Class* classes;
	_Student* student;
};
struct Filelist {
	std::string filename;
	Filelist* pNext = nullptr;
	Filelist* pPrev = nullptr;
};
std::ostream& operator<<(std::ostream& os, const Date& dt);
std::wostream& operator<<(std::wostream& os, const Date& dt);
bool operator==(Date a, Date b);
bool operator<(Date a, Date b);
bool operator<=(Date a, Date b);
bool operator>(Date a, Date b);
bool operator>=(Date a, Date b);


void AddInListFile(Filelist*& direc, std::string add);
void AddStudent(_Student*& studentlist, Student* student);
Student* StringToStudent(std::wstring str);
_Student* FileInStudent(std::string filename);
void StuToBin(Student* stu, std::string fileout);
Student* BinToStu(std::string filein);
void SaveNewStu(_Student* stu, char* directon);
void FileOutStudent(_Student* stu, std::string fileout);
void PrintStu(Student* a);
void PrintStu(_Student* stu);
void PrintStu(Student** stu);
Classes* LoadClass(const char* filein);
SchoolYear* AddSchoolYear(int year);
_Student* TypeInStudent();
void SaveSchoolYear(SchoolYear* sch);
void CourseToBin(Course* course, std::string filename, std::string current);
Course* BinToCourse(std::string filename);
void MakeCurentTime(int year);
std::string ViewSemesterTime();
int CountFile(Filelist* a);

Course* MakeCourse();
void MakeCourse(std::string current);
void CourseToBin(_Course* course, std::string current);

Classes MakeClass(_Student*& all, bool cls = true, int x = 5, int y = 2);
void SaveClass(Classes cl,const char* fileout);


void LoginStu(Student*& CurrentUser);
void Logout(Student* CurrentUser);
void ChangeInfo(Student*& CurrentUser);
_Student* SearchStuList(unsigned __int64* ID);
Student* SearchStu(unsigned __int64 ID);
Student** SearchStuArr(unsigned __int64* ID, std::string Grade);
std::string TakeCurrent();
void displayScore(Score* a);
void displayCourse(Course* cou);
wchar_t* RemoveSpace(wchar_t* a);
#endif // _Structs

