#ifndef _DataProject
#define _DataProject

#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<codecvt>
#include<Windows.h>
#include <conio.h>
#ifndef _StructData
#define _StructData
// the struct use for whole program
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
	unsigned __int64 ID;
	float totals = 0;
	float finals = 0;
	float mids = 0;
	float others = 0;
};
struct Course
{
	char* ID;
	wchar_t* name;
	wchar_t* teacher;
	unsigned short credit;
	struct Performed
	{
		unsigned short day = 0;
		unsigned short session = 0;
	};
	Performed performed[2];
	unsigned short numberofstudent = 0;
	unsigned short maxstudent = 50;
	unsigned __int64* stuID = nullptr;
	Score* score = nullptr;
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
	int numberofstudent = 0;
	unsigned __int64* ID;
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
	_Class* classes;
	_Student* student;
};
struct Filelist {
	std::string filename;
	Filelist* pNext = nullptr;
	Filelist* pPrev = nullptr;
};
#endif // !_StructData

#ifndef _FuncData
#define _FuncData
int CountStudent(_Student* a);

//------------Date
Date GetTime();
Date InputDate();
Date TakeDateStart(std::string current);
Date TakeDateEnd(std::string current);
std::ostream& operator<<(std::ostream& os, const Date& dt);
std::wostream& operator<<(std::wostream& os, const Date& dt);
bool operator==(Date a, Date b);
bool operator<(Date a, Date b);
bool operator<=(Date a, Date b);
bool operator>(Date a, Date b);
bool operator>=(Date a, Date b);
bool LeapYear(int y);
bool CheckDate(Date dat);
//***********************************************************

//------------Score
Score* LoadScore(std::string filename);
void SaveScore(Course* cou, std::string filename);
void SaveScore(Course* cou, Score* score, std::string filename);
Score GetStuScore(std::string path, unsigned __int64 ID);
Score GetScore(unsigned __int64 ID, char* coursename);
void GetGPA(Student* a);
//***********************************************************

//------------Course
Course* MakeCourse();
Course* BinToCourse(std::string filename);
Course* searchCourseFile(std::string search);
void AddCourse(_Course*& courselist, Course* course);
void CourseToBin(_Course* course, std::string current);
void CourseToBin(Course* course, std::string filename, std::string current);
void MakeCourse(std::string current);
bool isConflict(Course* a, Course* b);
void SessionConflict(Course** a, Course** b, int*& Register);
void registerCourse(Student* stu, Course** cou, std::string sem);
void classifyCourse(Course** reg, Course** wasReg, Course**& cancelReg, Course**& newReg);
void registerCourse(Course** newReg, std::string sem, unsigned __int64 stuID);
void cancelCourse(Course** cancelReg, std::string sem, unsigned __int64 stuID);

//***********************************************************

//------------Student
_Student* TypeInStudent();
_Student* FileInStudent(std::string filename);
_Student* SearchStuList(unsigned __int64* ID);
Student* BinToStu(std::string filein);
Student* StringToStudent(std::wstring str);
Student* SearchStu(unsigned __int64 ID);
Student** SearchStuArr(unsigned __int64* ID, std::string Grade);
std::string GetFilePath(unsigned __int64 ID);

void SaveNewStu(_Student* stu, char* directon);
void FileOutStudent(_Student* stu, std::string fileout);
void StuToBin(Student* stu, std::string fileout);
void AddStudent(_Student*& studentlist, Student* student);
void removeAcourseForStudents(int* studentsIDs, char* courseID);
//***********************************************************


//------------Classes
Classes MakeClass(_Student*& all, bool cls = true, int x = 5, int y = 2);
Classes* LoadClass(const char* filein);
void AddClass(_Class*& cls, Classes sourse);
void SaveClass(_Class* cls, char* direction);
void SaveClass(Classes cl, const char* fileout);
void PrintClass(Classes a);
//***********************************************************

//------------FileList
int CountFile(Filelist* list);
Filelist* TakeFileInFolder(const std::wstring& name);
Filelist* TakeFileInFolder(const std::string& name);
std::string ChoseFolder(Filelist* list, short x, short y);
void AddInListFile(Filelist*& direc, std::string add);
void DeleteCurFileList(Filelist*& filelist);
//***********************************************************

#endif // !_FuncData

#ifndef _DeallocateData
#define _DeallocateData

void deleteStu(Student*& a);
void deleteStu(Student**& a);
void delete_Stu(_Student*& a);
void deleteCourse(Course*& a);
void deleteCourse(Course**& a);
void delete_Course(_Course*& a);
void deleteClasses(Classes*& a);
void deleteClasses(Classes**& a);
void deleteSemester(Semester*& a);
void deleteSchoolyear(SchoolYear*& a);
void deleteFilelist(Filelist*& a);
void deleteIntArray(int*& a);
void deleteIntArray(unsigned __int64*& a);
void deleteStuArray(Student**& a);

#endif // !_DealocateData


#endif // !_Data
