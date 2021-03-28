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
	char* password;
};
struct Score
{
	unsigned int ID;
	char* name;
	float totals, finals, mids, others;
};
struct Course
{
	char* ID;
	char* name;
	char* teacher;
	unsigned short credit;
	unsigned short numberofstudent = 0;
	unsigned short maxstudent = 50;
	Score* score;
	struct Performed
	{
		char day[4];
		char session[3];
	};
	Performed *performed;
};
struct Student
{
	unsigned __int32 ID;
	wchar_t* fistname, *lastname;
	char gender;
	Date birth;
	unsigned __int64 SocialID;
	char* coursenow=nullptr;
	char* allcourse=nullptr;
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

void AddClass(SchoolYear schoolyear, Classes classes);
void AddClass(SchoolYear schoolyear, std::string filein);

Student* FindStudent(_Student* student, unsigned __int32 ID);
Student* FindStudent(_Student* student, char* username);
Course* FindCourse(_Course course, char* ID);
Course* FindCourse(SchoolYear schoolyear, char* ID);
Course* FindCourse(SchoolYear* schoolyear, char* ID);
Score FindScore(char* courseID, unsigned __int32 studentID);
Classes* FindClass(SchoolYear* schoolyear, char* classname);

Classes InputClass(std::wstring name, _Student* stu);
#endif // !_NewStruct