#ifndef _Structs
#define _Structs
#include<iostream>
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
	unsigned int ID;
	wchar_t* name;
	float totals, finals, mids, others;
};
struct Course
{
	char* ID;
	wchar_t* name;
	wchar_t* teacher;
	unsigned short credit;
	unsigned short numberofstudent = 0;
	unsigned short maxstudent = 50;
	unsigned __int64* stuID;
	Score* score;
	struct Performed
	{
		char day[4];
		char session[3];
	};
	Performed* performed;
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
	Student* student = nullptr;
	unsigned __int64* ID;
};
struct _Student
{
	Student student;
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
	Course course;
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

std::ostream& operator<<(std::ostream& os, const Date& dt);
std::wostream& operator<<(std::wostream& os, const Date& dt);

void AddStudent(_Student*& studentlist, Student student);
Student StringToStudent(std::wstring str);
_Student* FileInStudent(std::string filename);
void StuToBin(Student* stu, std::string fileout);
Student BinToStu(std::string filein);
void SaveNewStu(_Student* stu, char* directon,const char* savefile);
void SchoolYearToBin(SchoolYear sch);
void FileOutStudent(_Student* stu, std::string fileout);
void PrintStu(Student* a);
void PrintStu(_Student* stu);
SchoolYear* AddSchoolYear();
void SaveSchoolYear(SchoolYear* sch, const char* savefile);
#endif // _Structs

