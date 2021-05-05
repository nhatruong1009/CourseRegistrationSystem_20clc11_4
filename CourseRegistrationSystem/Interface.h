#ifndef _Inter
#define _Inter
#include"Sup.h"

int secondrun();
int fistrun(std::string& current);

void GotoXY(short x, short y);
short Menu(wchar_t** list, short Xposition, short Yposition);
short Menu(char** list, short Xposition, short Yposition);
short Choose(wchar_t** list, short X, short Y);
short Choose(char** list, short X, short Y);
void pickSchedule(Course* cou, int x, int y);

void PrintStu(Student* a);
void PrintStu(_Student* stu);
void PrintStu(Student** stu, int c);

void displayCourse(Course* cou);
void displayCourse(Course** cou);
void displaylistCourse(Course* cou);
#endif // !_Inter