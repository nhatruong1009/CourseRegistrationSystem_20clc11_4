#ifndef _NewStructs
#define _NewStructs

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
	Score* score;
	Course* coursenow;
	Course* allcourse;
	Account account;
	float GPA;
};
struct Classes
{
	char* name;
	Student* student;
};
struct Semester
{
	Date start, end;
	Course* course;
};

#endif // !_NewStruct