#include"NewStructs.h"
#include<iostream>

struct Date
{
	unsigned dd, mm, yy;
};
struct Account
{
	std::string username;
	std::string password;
};
struct Score
{
	unsigned int ID;
	std::string name;
	float totals, finals, mids, others;
};
struct Course
{
	std::string ID;
	std::string name;
	std::string teacher;
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
	std::string fistname,lastname;
	bool gender;
	Date birth;
	unsigned long long SocialID;
	std::string* coursenow;
	std::string* allcourse;
	Account account;
	float GPA;
};
struct Semester
{
	Date start, end;
	_Course* course;
};
struct Classes
{
	std::string name;
	Student** student;
};
struct SchoolYear
{
	int year;
	Semester *semester;
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


void InputCourse() {
	Course course;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cout << "ID: "; std::getline(std::cin, course.ID);
	std::cout << "Course name: "; std::getline(std::cin, course.name);
	std::cout << "Teacher: "; std::getline(std::cin, course.teacher);
	std::cout << "Credit: "; std::cin >> course.credit;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
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
Course* FindCourse(_Course course, char* ID);
Course* FindCourse(SchoolYear schoolyear, char* ID);
Course* FindCourse(SchoolYear* schoolyear, char* ID);
Score FindScore(char* courseID, unsigned int studentID);
Classes* FindClass(SchoolYear* schoolyear, char* classname);
