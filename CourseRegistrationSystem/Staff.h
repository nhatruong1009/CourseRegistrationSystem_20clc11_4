#ifndef _StaffMode
#define _StaffMode
#include"Interface.h"
#include"Data.h"
#include"Sup.h"
#include"Student.h"

#ifndef _StaffMenuMode
#define _StaffMenuMode

void updateStudentsInClass(Classes& a);
void userTypeMode();
void staffMode(bool login=true);
void staffStudentMenu();
void gradeMenu();
void classMenu();
void studentMenuStaff();
void addGrade();
void ViewGrade();
void AddClass();
void DoSomeThingInClass(Classes* cls, std::string grade);
void ViewClass();
void courseStaff();
void schoolPlan();
void addCourseInSemmester(std::string current);
void addCourse();
void viewCourse();
void editCourse();
void resetRegister();
void timeRegister(std::string sem, Date startReg, Date endReg);
void OpenRegister();
std::string chooseTime(bool timeout = true,bool timestart=true);
#endif // !_StaffMenuMode

#ifndef _EditCourse
#define _EditCourse

unsigned short LStringToPerform(wchar_t* temp);
Course* StringToCourse(std::wstring str);
Course* searchID(_Course* courselist, std::wstring search);
Course* searchName(_Course* courselist, std::wstring search);
Course* searchTeacher(_Course* courselist, std::wstring search);
Course* searchCourse(_Course* courselist, std::wstring& search);
_Course* FileInCourse(std::string filename);
std::string GetFilePath(char* CourseID);
void FileOutCourse(_Course* cou, std::string fileout);
void searchScore(_Course* allcourse);
void editScore(Course* cou, std::string current);
void editCourse(Course* cou, std::string filename, std::string current);
void editInfo(Course* cou, std::string filename, std::string current);
void TypeInScore(Course* cou, std::string current);
void FileInScore(Course* cou, std::string current);
void editCourse(std::string filename, std::string current);
void deleteCourse(Course* cour, std::string filename, std::string current);
void displayScore(Score a);
#endif // !_EditCourse

#endif // !_StaffMode
