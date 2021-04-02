
#ifndef _Structs
#define _Structs

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
	unsigned __int32 ID;
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

void AddStudent(_Student*& studentlist, Student student);

#endif // _Structs

