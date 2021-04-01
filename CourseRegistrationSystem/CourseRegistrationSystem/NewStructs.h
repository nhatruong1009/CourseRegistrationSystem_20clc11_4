#ifndef _NewStructs
#define _NewStructs
#include<iostream>
#include<string>
#include<wchar.h>
struct Date
{
	unsigned int dd=0, mm=0, yy=0;
};
struct Account
{
	wchar_t* username;
	wchar_t* password;
};
struct Score
{
	unsigned int ID;
	wchar_t* name;
	float totals, finals, mids, others;
};
struct Course
{
	wchar_t* ID;
	wchar_t* name;
	wchar_t* teacher;
	unsigned short credit;
	unsigned short numberofstudent = 0;
	unsigned short maxstudent = 50;
	Score* score;
	struct Performed
	{
		wchar_t day[4];
		wchar_t session[3];
	};
	Performed *performed;
};
struct Student
{
	unsigned __int32 ID;
	wchar_t* firstname, *lastname;
	wchar_t gender;
	Date birth;
	unsigned __int64 SocialID;
	wchar_t** coursenow=nullptr;
	wchar_t** allcourse=nullptr;
	Account account;
	float GPA=0;
};
struct Classes
{
	wchar_t* name;
	Student* student=nullptr;
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
};

void cinclear();
void PrintStu(_Student* stu);
void PrintStu(Student* a);
void DealloStu(_Student*& stu);

void FileOutStudent(_Student* stu, std::wstring fileout);
std::ostream& operator<<(std::ostream& os, const Date& dt);
std::wostream& operator<<(std::wostream& os, const Date& dt);
void AddCourse(_Course courselist, Course course);
_Course* InputCorse(std::string filein);
void UpdateCourse(Course couse);
void RemoveCourse(_Course courselist, std::string ID);

Student InputStudent();
void AddStudent(_Student*& studentlist, Student student);
_Student* AddStudent(std::wstring filein);
void RemoveStudent(_Student* studentlist, unsigned __int32 ID);

Score InputScore();
void AddScore(Score* scoreboard, Score score);
Score* InputScore(std::string filein);

void AddClass(_Class*& classes, Classes cls);
void DealloClass(_Class*& cls);
Classes* FindClass(_Class* cls, wchar_t* name);

Student* FindStudent(_Student* student, unsigned __int32 ID);
Student* FindStudent(_Student* student, wchar_t* username);
Course* FindCourse(_Course course, wchar_t* ID);
Course* FindCourse(SchoolYear schoolyear, wchar_t* ID);
Course* FindCourse(SchoolYear* schoolyear, wchar_t* ID);
Score FindScore(wchar_t* courseID, unsigned __int32 studentID);
Classes* FindClass(SchoolYear* schoolyear, wchar_t* classname);
Classes InputClass(std::wstring name, _Student* stu);
#endif // !_NewStruct