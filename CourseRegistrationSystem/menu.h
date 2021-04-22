#ifndef _Menu
#define _Menu
#include"CommonFunc.h"
#include"Data.h"
bool isLoggedIn();
void enrollCourse(Student student, Course course);
void updateStudentsInClass(Classes& a);
void userTypeMode();
void studentMode(Student* stu=nullptr);
void staffMode();
void studentMenu();
void gradeMenu();
void classMenu();
void addGrade();
void staffStudentMenu();
void ViewGrade();
void AddClass();
void ViewClass();
void StuInformation(Student* stu);
void CourseInformaion(Student* stu);
void RegisterCouse(Student* stu);
void ViewCouse(Student* stu);
#endif // !_Menu