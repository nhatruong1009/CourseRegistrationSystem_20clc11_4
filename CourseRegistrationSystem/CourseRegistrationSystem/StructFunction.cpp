#include"NewStructs.h"
#include<iostream>

struct Date
{
	unsigned dd, mm, yy;
};
struct Account
{
	char* username;
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
	char* teacher;
	unsigned short credit;
	unsigned short Maxstudent = 50;
	Score* score;
	struct Performed
	{
		char day[4];
		char session[3];
	};
	Performed performed;
};
struct Student
{
	unsigned int ID;
	char* name;
	bool gender;
	Date birth;
	unsigned long long SocialID;
	_Course* coursenow;
	_Course* allcourse;
	Account account;
	float GPA;
};
struct Semester
{
	unsigned int ID;
	Date start, end;
	_Course* course;
};
struct Classes
{
	char* name;
	_Student* student;
};
struct SchoolYear
{
	int year;
	Semester semester[3];
	_Class* classes;
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

Course InputCourse();
void AddCourse(_Course courselist, Course course);
_Course* InputCorse(std::string filein);

Student InputStudent();
void AddStudent(_Student studentlist, Student student);
void AddtStudent(_Student studentlist, std::string filein);

Score InputScore();
void AddScore(Score* scoreboard, Score score);
Score* InputScore(std::string filein);

void AddClass(SchoolYear schoolyear, Classes classes);
void AddClass(SchoolYear schoolyear, std::string filein);

Student* FindStudent(_Student student, unsigned int ID);
Student* FIndStudent(_Student student, char* username);

Course*FindCourse()