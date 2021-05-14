#ifndef _StudentMode
#define _StudentMode
#include"Staff.h"
void SaveLoginHistory(char* AccountUsername);
void SaveLogoutHistory(char* AccountUsername);
void SaveCourseRegHis(char* AccountUsername, Course course);
void SaveCourseCancelHis(char* AccountUsername, Course course);

bool isLoggedIn();
void Logout(Student* CurrentUser);
void LoginStu(Student*& CurrentUser);
void studentMode(Student* stu=nullptr);
void StuInformation(Student* stu);
void ViewCourseNow(Student* stu);
void CourseInformaion(Student* stu);
void ViewCouse(Student* stu);
void registerMenu(Student* stu);
inline void removereg(Course** reg, Course* re);
void takeCourseReg(Course** course, int*& take, Student* stu, std::string current,int m=5);
void ChangeInfo(Student*& CurrentUser);
#endif // !_StudentMode

