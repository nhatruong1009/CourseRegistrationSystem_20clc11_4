#include"menu.h"
#include"Data.h"
#include"CommonFunc.h"

void deleteAccount(Account& a) {
	delete a.username;
	delete a.password;
}
void deleteScore(Score*& s) {
	delete[] s->name;
}
void deleteCourse(Course*& c) {
	delete c->ID, c->name, c->teacher;
	delete[] c->performed;
	deleteScore(c->score);
}
void deleteCourseNow(char** c) {
	int n = _msize(c) / sizeof(char*);
	for (int i = 0; i < n; i++) {
		c[i] = nullptr;
	}
	delete c, c = nullptr;
}
void deleteStudent(Student*& s) {
	delete s->firstname, s->lastname;
	deleteCourseNow(s->allcourse);
	deleteCourseNow(s->coursenow);
	deleteAccount(s->account);
}
void deleteClasses(Classes& c) {
	delete[] c.name, c.ID;
}
void delete_Student(_Student*& s) {
	while (s != nullptr) {
		_Student* pTemp = s;
		deleteStudent(pTemp->student);
		s = s->pNext;
		delete pTemp;
	}
}
void delete_Class(_Class*& s) {
	while (s != nullptr) {
		_Class* pTemp = s;
		s = s->pNext;
		delete pTemp;
	}
}
void delete_Course(_Course*& s) {
	while (s != nullptr) {
		_Course* pTemp = s;
		deleteCourse(pTemp->course);
		s = s->pNext;
		delete pTemp;
	}
}
void deleteSemester(Semester*& s) {
	delete_Course(s->course);
}
void deleteSchoolYear(SchoolYear*& s) {
	deleteSemester(s->semester);
	delete_Class(s->classes);
	delete_Student(s->student);
}
void deleteFilelist(Filelist*& s) {
	while (s != nullptr) {
		Filelist* pTemp = s;
		s = s->pNext;
		delete pTemp;
	}
}
