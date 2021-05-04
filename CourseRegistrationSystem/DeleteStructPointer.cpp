#include"menu.h"
#include"Data.h"
#include"CommonFunc.h"


//void deleteAccount(Account& a) {
//	delete[] a.username;
//	delete[] a.password;
//}
//void deleteScore(Score*& s) {
//	delete[] s->name;
//}
//void deleteCourse(Course*& c) {
//	delete[] c->ID, c->name, c->teacher, c->stuID;
//	deleteScore(c->score);
//}
//void deleteCourseNow(char** c) {
//	int n = _msize(c) / sizeof(char*);
//	for (int i = 0; i < n; i++) {
//		delete[] c[i];
//	}
//	delete[] c;
//}
//void deleteStudent(Student*& s) {
//	delete s->firstname, s->lastname;
//	deleteCourseNow(s->allcourse);
//	deleteCourseNow(s->coursenow);
//	deleteAccount(s->account);
//}
//void deleteClasses(Classes& c) {
//	delete[] c.name, c.ID;
//}
//void delete_Student(_Student*& s) {
//	while (s != nullptr) {
//		_Student* pTemp = s;
//		deleteStudent(pTemp->student);
//		s = s->pNext;
//		delete pTemp;
//	}
//}
//void delete_Class(_Class*& s) {
//	while (s != nullptr) {
//		_Class* pTemp = s;
//		s = s->pNext;
//		delete pTemp;
//	}
//}
//void delete_Course(_Course*& s) {
//	while (s != nullptr) {
//		_Course* pTemp = s;
//		deleteCourse(pTemp->course);
//		s = s->pNext;
//		delete pTemp;
//	}
//}
//void deleteSemester(Semester*& s) {
//	delete_Course(s->course);
//}
//void deleteSchoolYear(SchoolYear*& s) {
//	deleteSemester(s->semester);
//	delete_Class(s->classes);
//	delete_Student(s->student);
//}
//void deleteFilelist(Filelist*& s) {
//	while (s != nullptr) {
//		Filelist* pTemp = s;
//		s = s->pNext;
//		delete pTemp;
//	}
//}


void deleteStu(Student*& a)
{
	delete[]a->account.password;
	delete[]a->account.username;
	delete[]a->firstname;
	delete[]a->lastname;
	if (a->coursenow)
	{
		int n = _msize(a->coursenow) / sizeof(a->coursenow);
		for (int i = 0; i < n; i++)
			delete[]a->coursenow[i];
		delete[]a->coursenow;
	}
	if (a->allcourse)
	{
		int n = _msize(a->allcourse) / sizeof(a->allcourse);
		for (int i = 0; i < n; i++)
			delete[]a->allcourse[i];
		delete[]a->allcourse;
	}
	delete a;
	a = nullptr;
}

void delete_Stu(_Student*& a)
{
	if (a == nullptr)
		return;
	_Student* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Student* temp = cur;
		cur = cur->pNext;
		deleteStu(temp->student);
		delete temp;
	}
	deleteStu(cur->student);		// Deallocate First Node 
	delete cur;
	a = nullptr;
}

void deleteCourse(Course*& a)
{
	delete[]a->ID;
	delete[]a->name;
	delete[]a->teacher;
	if(a->stuID)
		delete[]a->stuID;
	if (a->score)
	{
		int n = _msize(a->score)/sizeof(a->score);
		for (int i = 0; i < n; i++) {
			delete[] a->score[i].name;
		}
		delete a->score;
	}
	delete a;
	a = nullptr;
}

void delete_Course(_Course*& a)
{
	if (a == nullptr)
		return;
	_Course* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Course* temp = cur;
		cur = cur->pNext;
		deleteCourse(temp->course);
		delete temp;
	}
	deleteCourse(cur->course);		// Deallocate First Node 
	delete cur;
	a = nullptr;
}

void deleteClasses(Classes*& a)
{
	delete[]a->name;
	delete[]a->ID;
	delete a;
	a = nullptr;
}

void deleteClasses(Classes& a)
{
	delete[]a.name;
	delete[]a.ID;
}

void delete_Class(_Class*& a)
{
	if (a == nullptr)
		return;
	_Class* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		_Class* temp = cur;
		cur = cur->pNext;
		delete temp;
	}
	// Deallocate First Node 
	delete cur;
	a = nullptr;
}

void deleteSemester(Semester* a)
{
	delete_Course(a->course);
	delete a;
}

void deleteSchoolyear(SchoolYear*& a)
{
	int n = _msize(a->semester) / sizeof(a->semester);
	for (int i = 0; i < n; i++) {
		deleteSemester(&a->semester[i]);
	}
	delete_Class(a->classes);
	delete_Stu(a->student);
	delete a;
}

void deleteFilelist(Filelist*& a)
{
	if (a == nullptr)
		return;
	Filelist* cur = a->pNext;
	while (cur != a)	// Deallocate Second Node afterwards
	{
		Filelist* temp = cur;
		cur = cur->pNext;
		delete temp;
	}
	// Deallocate First Node 
	delete cur;
	a = nullptr;
}

void deleteIntArray(int*& a)
{
	delete[]a;
}

void deleteIntArray(unsigned __int64*& a)
{
	delete[]a;
	a = nullptr;
}

void deleteStuArray(Student**& a)
{
	if (a == nullptr)
		return;
	int n = _msize(a) / sizeof(a);
	for (int i = 0; i < n; i++)
	{
		if(a[i])
			deleteStu(a[i]);
	}
	delete[]a;
	a = nullptr;
}