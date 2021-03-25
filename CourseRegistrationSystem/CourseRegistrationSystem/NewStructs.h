#ifndef _NewStructs
#define _NewStructs
#include<iostream>
struct Node
{
	void* data;
	Node* pNext;
	Node* pPrev;
};
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
	Node* coursenow;
	Node* allcourse;
	Account account;
	float GPA;
};
struct Semester
{
	unsigned int ID;
	Date start, end;
	Node* course;
};
struct Classes
{
	char* name;
	Node* student;
};
struct SchoolYear
{
	int year;
	Semester semester[3];
	Node* classes;
};

void AddToNode(Node*& pHead, void* data);

#endif // !_NewStruct